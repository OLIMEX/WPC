/* 2013-07-07 by kantal59
   License: GPL
   Compile: g++ -std=c++0x -o postfix postfix.cpp

   OLIMEX WPC#16:
            Input string which is mathematical statement written in normal Infix Notation and convert it to Postfix Notation.
   
  You can put additional operators into the 'operators' vector. 
  It is not for speed:-) and all objects are created in the stack. 
*/

#ifndef POSTFIX_H
#define POSTFIX_H

#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

class Postfix {

    enum objectType { tOperator, tOperand};    
    enum Priority {     pri_add=1, 
                        pri_sub= pri_add, 
                        pri_mul, 
                        pri_div, 
                        pri_neg, 
                        pri_leftbr, 
                        pri_sqrt= pri_leftbr, 
                        pri_pow= pri_leftbr,
                        pri_rightbr,
                        pri_comma= pri_rightbr 
                          
    };

    struct Operator {
	     string token;
	     Priority priority;
	     unsigned char nop;	    // number of operands
	     double (*operation) ( double lnum, double rnum ) ; 
	     Operator( string tkn, Priority prio, char operands, double (*f) ( double lnum, double rnum ) ): 
	               token(tkn), priority(prio), nop(operands), operation( f){};
    };
 
    struct Object{
        objectType type;
        union Obj {
            double val;     // operand 
            int index;      // index in operators
        } obj;
        Object( objectType typ, double d): type(typ) { obj.val=d;};
        Object( objectType typ, int i): type(typ) { obj.index=i;};
        Object( objectType typ): type(typ) { obj.val=0;};
    };
    
    string expr;                // expression to be processed  
    vector<Operator> operators; // operator objects, it must be initialized once
    vector<int> opi;            // operator work stack 
    vector<Object> pfix;        // the result in postfix notation
    
    int negIndex, rightbrIndex, leftbrIndex, commaIndex;
	bool DEBUG;
	
    public:
    
    Postfix( const string &expression);
    ~Postfix(){ }
    int parsing();
    double evaluate();
    void error( const string& str){ cout<<"--ERROR: "<< str<<endl; }
    string str();
    void debug( int index);
    void setDebug( bool b){ DEBUG=b;}
    
};// Postfix class end    
    
//--------------------------------------------------
    Postfix::Postfix( const string &expression)
//--------------------------------------------------    
{
        expr="("+ expression+ ")";
    
     	operators.push_back( Operator( "+", pri_add,2, [](double lnum, double rnum){ return(lnum+rnum);} ) ); 
	    operators.push_back( Operator( "-", pri_sub,2, [](double lnum, double rnum){ return(lnum-rnum);} ) ); 
	    operators.push_back( Operator( "*", pri_mul,2, [](double lnum, double rnum){ return(lnum*rnum);} ) );
	    operators.push_back( Operator( "/", pri_div,2, [](double lnum, double rnum){ return(lnum/rnum);} ) );
	    operators.push_back( Operator( "neg", pri_neg,1,[](double d, double dummy){ return( -d);} ) );
	        negIndex= operators.size()-1;
	    operators.push_back( Operator( "(", pri_leftbr,0,NULL) );
	        leftbrIndex= operators.size()-1;
	    operators.push_back( Operator( ")", pri_rightbr,0,NULL) );
	        rightbrIndex= operators.size()-1;
	    operators.push_back( Operator( ",", pri_rightbr,0,NULL) );  // ',' for operators with two operands, e.g.: pow(2,10)
	        commaIndex= operators.size()-1;
	    operators.push_back( Operator( "sqrt(", pri_leftbr,1,  [](double d, double dummy){ return( sqrt(d));} ) );
	    operators.push_back( Operator( "exp(",  pri_leftbr,1,  [](double lnum, double dummy){ return( exp(lnum));} ) );
	    operators.push_back( Operator( "pow(",  pri_leftbr,2,  [](double d, double ex){ return( pow(d,ex));} ) );
	
	    DEBUG= false;
};	    
    
//-------------------------------    
    int Postfix::parsing( )
//-------------------------------    
{
        opi.clear();
        pfix.clear();
        
       	// remove whitespaces
    	string::iterator it= remove_if( expr.begin(), expr.end(), [](char c){ return( c==' ' || c=='\t' || c=='\n' ); } );
    	expr.resize( it - expr.begin());
	
    	int prevElement= tOperator;
    	int prevOperatorIndex= 0;
	    
	
    	for( int idx=0; idx<expr.size();){ 
	    	// search for an operator:
	    	int max_tknlth=0;
		    int operator_found= -1;
	        if( DEBUG) debug(idx);
	    	for(int i=0; i<operators.size(); i++){		
	    	    int tknlth= operators[i].token.length();
	    	    if( operators[i].token.compare( 0, tknlth, expr.substr(idx,tknlth)) !=0 ) continue;
	    	    if( tknlth > max_tknlth ) { operator_found=i; max_tknlth= tknlth; } 
	    	}
	    	
	    	
	    	if( operator_found== -1 ){  // operator isn't found: try to get a number
	    	    double d;
	    	    size_t ilast;
	    	    try{
                        d= stod( expr.substr(idx), &ilast); 
                }
                catch (const std::invalid_argument& ia){
	                    error("Nor an operator neither a number found");  return(-1);
                }     
	    	    
		        idx+= ilast;
		        prevElement= tOperand;
		        pfix.push_back( Object( tOperand, d) );
		        continue;
		    }
		    
    		//-------- an operator found:	
    		switch( operators[ operator_found].priority){
    		
    		    case pri_leftbr:
    		                        opi.push_back( operator_found );
    		                        break;
    		    
    		    case pri_rightbr:{  // popping until a left bracket found: '(', 'sqrt(' , 'pow(', etc.
                                    bool leftbr_found=false;
                                    while( opi.size()){
                                        int k= opi.back();
                                        if( operators[k].priority==pri_leftbr){
                                            leftbr_found= true;
                                            if( operator_found != commaIndex){
                                                 opi.pop_back();  // e.g.: leave 'pow(' in opi if the arg separator ',' found 
                                                // '(' will not be put into pfix:
                                                if( k != leftbrIndex) pfix.push_back( Object( tOperator, k ));
                                            }    
                                            break;
                                        }
                                        pfix.push_back( Object( tOperator, k ));
                                        opi.pop_back();
                                    }
                                    if( leftbr_found==false ){ error("Left bracket not found"); return(-1); }
                                    break;
                }                                    
                                    
                default: // "+5..."  --> '+' won't be stored:
				    if(     operators[operator_found].token == "+" && prevElement==tOperator 
				        &&  prevOperatorIndex != rightbrIndex ) break;  
				        
				        // "-5..." replaced with "neg5..."
				    if(       operators[operator_found].token == "-" && prevElement==tOperator 
				        &&  prevOperatorIndex != rightbrIndex ){ 
				        
						operator_found= negIndex;
				    } 
				    
                    if(  !opi.size()  ||  operators[ opi.back()].priority== pri_leftbr
                        || ( operators[ operator_found].priority > operators[ opi.back()].priority ) ){
                        
                        opi.push_back( operator_found);
                        break;
                    }			
                    
                    while( opi.size() && operators[ opi.back()].priority != pri_leftbr ){ 
                        pfix.push_back( Object( tOperator, opi.back()) );
                        opi.pop_back();
                    }
                    opi.push_back( operator_found);
                    break;                             
    		}   //switch 
    		
    		if( operator_found== negIndex ) idx+=1;
             else idx+= operators[ operator_found ].token.length();
             
		    prevElement= tOperator;
		    prevOperatorIndex= operator_found;
		    
        }   // for 
        
        return(0);
}        		
    		
//---------------------------------    
    double Postfix::evaluate()
//---------------------------------
{
        vector<Object> pf= pfix;
        double d;
        
            vector<Object>::iterator it;
            
            while( (it= find_if( pf.begin(), pf.end(), [](Object o){ return( o.type==tOperator ); } )) != pf.end() ){
            
                    int index= it->obj.index; 
                    char nop= operators[ index ].nop;
                    
                    if( nop==1 ){ 
                        if( (it-pf.begin()) >= 1   &&  (it-1)->type== tOperand ){
                            d= operators[index].operation( (it-1)->obj.val, 0);
                        }
                        else{ error("Missing operand(1)"); return(0); }    
                    }
                    if( nop==2 ){
                        if( (it-pf.begin()) >= 2  &&  (it-1)->type== tOperand  &&  (it-2)->type== tOperand  ){
                            d= operators[index].operation( (it-2)->obj.val, (it-1)->obj.val);
                        }
                        else{ error("Missing operand(2)"); return(0); } 
                    }
                    
                    *it= Object( tOperand,d);
                    pf.erase( it-nop, it );     // erasing from vector is expensive, but I don't care :-)
            } 
            
        
            if( pf.size()!=1 || pf[0].type != tOperand ){ error("Syntax problem"); return(0);}
            return( pf[0].obj.val );
}
    

//------------------------------  		
    string Postfix::str() 
//------------------------------    
{
        ostringstream oss;
        for(int i=0; i<pfix.size(); i++){
            Object obi= pfix[i];
            if( obi.type== tOperand) oss<< obi.obj.val<<", ";
            else{
                string stkn= operators[ obi.obj.index].token;
                if( stkn.size()>1 && stkn.back()=='(' ) stkn.resize( stkn.size()-1); 
                oss<< stkn<<", " ;
            } 
        }        
        return( oss.str());
}

//--------------------------------------
    void Postfix::debug( int index)
//--------------------------------------    
{
        cout<< "opi("<<opi.size()<<")--> ";
        for(int i=0; i<opi.size(); i++){ cout<<operators[ opi[i]].token<<',';}
        cout<<"\npfix("<<pfix.size()<<")--> "<<str()<<endl;
        cout<<"expr--> "<< expr.substr(index)<<endl<<endl;
}
    
//---------------------------------------------------------------------------------------
    ostream& operator<< ( ostream& os, Postfix& pf){   return os << pf.str(); }  
//---------------------------------------------------------------------------------------    

	
#endif 


