/*
* ============================================================================
*  Name         : snake.js
*  Part of      : Snake
*  Description  : Simple snake game with incrementing speed for higher scores
*				  Based on tutorial from the code player http://bit.ly/1hVrHo0
*  Author       : Leon Anavi
*  Email        : leon@anavi.org
*
* ============================================================================
*/

$(document).ready(function(){
	
	//Canvas stuff
	var canvas = $("#canvas")[0];
	var ctx = canvas.getContext("2d");
	var w = $("#canvas").width();
	var h = $("#canvas").height();
	
	//Lets save the cell width in a variable for easy control
	var cw = 10;
	var sDirection = "right";
	var food = null;
	var score = 0;
	var nRefreshRate = 200;
	
	//Lets create the snake now
	var snake_array; //an array of cells to make up the snake
	
	function changePaintInterval()
	{
		if("undefined" != typeof game_loop) 
		{
			clearInterval(game_loop);
		}
		game_loop = setInterval(paint, nRefreshRate);
	}
	
	function init()
	{
		sDirection = "right"; //default direction
		create_snake();
		create_food(); //Now we can see the food particle
		//finally lets display the score
		score = 0;
		nRefreshRate = 120;
		changePaintInterval();
	}
	
	init();
	
	function create_snake()
	{
		var length = 5; //Length of the snake
		snake_array = []; //Empty array to start with
		for(var i = length-1; i>=0; i--)
		{
			//This will create a horizontal snake starting from the top left
			snake_array.push({x: i, y:0});
		}
	}
	
	//Lets create the food now
	function create_food()
	{
		food = {
			x: Math.round(Math.random()*(w-cw)/cw), 
			y: Math.round(Math.random()*(h-cw)/cw), 
		};
		//This will create a cell with x/y between 0-44
		//Because there are 45(450/10) positions accross the rows and columns
	}
	
	//Lets paint the snake now
	function paint()
	{
		//To avoid the snake trail we need to paint the BG on every frame
		//Lets paint the canvas now
		ctx.fillStyle = "black";
		ctx.fillRect(0, 0, w, h);
		ctx.strokeStyle = "white";
		ctx.strokeRect(0, 0, w, h);
		
		//The movement code for the snake to come here.
		//The logic is simple
		//Pop out the tail cell and place it infront of the head cell
		var nx = snake_array[0].x;
		var ny = snake_array[0].y;
		//These were the position of the head cell.
		//We will increment it to get the new head position
		//Lets add proper direction based movement now
		if(sDirection == "right") nx++;
		else if(sDirection == "left") nx--;
		else if(sDirection == "up") ny--;
		else if(sDirection == "down") ny++;
		
		//Lets add the game over clauses now
		//This will restart the game if the snake hits the wall
		//Lets add the code for body collision
		//Now if the head of the snake bumps into its body, the game will restart
		if(nx == -1 || nx == w/cw || ny == -1 || ny == h/cw || check_collision(nx, ny, snake_array))
		{
			//restart game
			init();
			//Lets organize the code a bit now.
			return;
		}
		
		//Lets write the code to make the snake eat the food
		//The logic is simple
		//If the new head position matches with that of the food,
		//Create a new head instead of moving the tail
		if(nx == food.x && ny == food.y)
		{
			var tail = {x: nx, y: ny};
			score++;
			
			if ( (50 < nRefreshRate) && (0 == (score%2)) )
			{
				nRefreshRate -= 10;
			}
			
			changePaintInterval();
			//Create new food
			create_food();
		}
		else
		{
			var tail = snake_array.pop(); //pops out the last cell
			tail.x = nx; tail.y = ny;
		}
		//The snake can now eat the food.
		
		snake_array.unshift(tail); //puts back the tail as the first cell
		
		for(var i = 0; i < snake_array.length; i++)
		{
			var sColor = (0 == i) ? "red" : "green";
			var c = snake_array[i];
			//Lets paint 10px wide cells
			paint_cell(c.x, c.y,sColor);
		}
		
		//Lets paint the food
		paint_cell(food.x, food.y, "yellow");
		//Lets paint the score
		var score_text = "Score: " + score;
		ctx.fillStyle = "white";
		ctx.fillText(score_text, 5, h-5);
	}
	
	//Lets first create a generic function to paint cells
	function paint_cell(x, y, sColor)
	{
		ctx.fillStyle = sColor;
		ctx.fillRect(x*cw, y*cw, cw, cw);
		ctx.strokeStyle = "black";
		ctx.strokeRect(x*cw, y*cw, cw, cw);
	}
	
	function check_collision(x, y, array)
	{
		//This function will check if the provided x/y coordinates exist
		//in an array of cells or not
		for(var i = 0; i < array.length; i++)
		{
			if(array[i].x == x && array[i].y == y)
			 return true;
		}
		return false;
	}
	
	//Lets add the keyboard controls now
	$(document).keydown(function(e){
		var key = e.which;
		//We will add another clause to prevent reverse gear
		if(key == "37" && sDirection != "right") sDirection = "left";
		else if(key == "38" && sDirection != "down") sDirection = "up";
		else if(key == "39" && sDirection != "left") sDirection = "right";
		else if(key == "40" && sDirection != "up") sDirection = "down";
		//The snake is now keyboard controllable
	})
});