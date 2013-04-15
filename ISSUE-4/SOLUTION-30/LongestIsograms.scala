// This is my second program in Scala. This is a programming exercise.
object LongestIsograms {
  val help = """Author: Emiliano Daddario
    |Tested on Scala 2.9.2
    |Program which finds the longest isograms in a XML page (JavaScript is disabled),
    |written in an (almost) functional paradigm.
    |An isogram is a word with no (alphanumeric?) duplicate chars (case-insensitive).
    |Text must be in English (i.e. alphabetic special characters may cause errors).
    |Check with a browser that the page _FINISHES_ loading soon, before running this.
    |Command-line usage: scala LongestIsograms.scala http://URL enclosingXMLTagName
    |Only the text inside the _FIRST_ <enclosingXMLTagName> tag in the page is tried.
    |enclosingXMLTagName is optional (default value is "body")|""".stripMargin
  import scala.collection.mutable.ArrayBuffer
  import scala.collection.immutable.TreeMap
  import scala.io.Source
  import scala.xml.XML.loadString
  import scala.annotation.tailrec
  // http://stackoverflow.com/questions/13625024/how-to-read-a-text-file-with-mixed-encodings-in-scala-or-java
  import java.nio.charset.CodingErrorAction
  import scala.io.Codec
  implicit val codec = Codec("UTF-8")
  codec.onMalformedInput(CodingErrorAction.REPLACE)
  codec.onUnmappableCharacter(CodingErrorAction.REPLACE)
  def main(args: Array[String]) {
    if (args.nonEmpty && args(0) == "--help") {
      println(help)
      sys.exit(0)
    }
    val defaultUrl = """http://archive.org/stream/alicesadventur00carr/alicesadventur00carr_djvu.txt"""
    val defaultTagName = "body"
    val url = if (args.isEmpty) {
      Console.err.println("Warning: no URL specified. Using the following:\n" + defaultUrl)
      defaultUrl
    } else
      args(0)
    val enclosingXMLTagName = if (args.isEmpty)
      // In the HTML source code of the page located at defaultUrl,
      // this is the name of the tag which contains the full text
      // of "Alice's Adventures in Wonderland"
      "pre"
    else if (args.length == 1) {
      Console.err.println("Warning: the name of the tag enclosing the text wasn't specified. Using \"" + defaultTagName + "\".")
      defaultTagName
    } else
      args(1)
    Console.err.println("Message: downloading (this may take some time)...")
    val source = try
      Source.fromURL(url) //(io.Codec("UTF-8"))
    catch {
      case ex: Exception => {
        Console.err.println("Error: a problem occurred during download. Exiting...")
        sys.exit(1)
      }
    }
    Console.err.println("Message: done downloading. Analyzing...")
    val html = source.mkString.toLowerCase
    // (?s) = enables DOTALL option
    // JVM doesn't support conditional regex
    val needle = "(?s)<" + enclosingXMLTagName + ".*?"
    val needle1 = (needle + "</" + enclosingXMLTagName + ">").r
    val needle2 = (needle + "$").r
    def strip(enclosingTag: String): String = {
      try
        loadString(enclosingTag).text
      catch {
        case ex: org.xml.sax.SAXParseException => {
          Console.err.println("""Warning: can't strip tags due to invalid XML. Maybe results will show the right
            					  |words anyway if text is long, but likely with wrong positions in word sequence."""
            .stripMargin)
          enclosingTag
        }
      }
    }
    val text = needle1.findFirstIn(html) match {
      // Try to strip HTML from enclosing tag using loadString
      case Some(enclosingTag) =>
        strip(enclosingTag)
      case None => {
        // Closing tag </enclosingXMLTagName> was not found, match until the end of the string
        needle2.findFirstIn(html) match {
          case Some(enclosingTag) =>
            Console.err.println("Warning: closing tag </" + enclosingXMLTagName + "> not found. Continuing till end of file.")
            strip(enclosingTag)
          case None =>
            Console.err.println("Error: no <" + enclosingXMLTagName + "> tags found. Exiting...")
            sys.exit(1)
        }
      }
    }
    // nonAlphabetic = regex string which matches one or more non-alphanumeric characters
    // [a-zA-Z0-9] = character class of _ENGLISH_ alphanumeric characters 
    // ^ = negates the character class
    // + = one or more occurrences
    val nonAlphabetic = "[^a-zA-Z0-9]+"
    // Of course words are separated by non-alphabetic characters
    val words = if (text != "") text.split(nonAlphabetic) else Array[String]()
    // From now on, in any variable name, "By" stands for "grouped by"
    val wordsByLength = words.groupBy(_.length)
    // sort Map by converting to TreeMap
    // TreeMap = a Map automatically sorted in ascending order 
    // _* = type annotation to interpret an array as Scala's repeated parameters
    val wordsByLengthAscending = TreeMap(wordsByLength.toArray: _*)
    val wordsByLengthDescending = wordsByLengthAscending.toList.reverse
    def isIsogram(word: String): Boolean = {
      val chars = word.toList
      // chars.distinct = unique characters
      chars.length == chars.distinct.length
    }
    def filterIsograms(words: (Int, Array[String])): Array[String] = words._2.filter(isIsogram)
    val isogramsByLengthDescending = wordsByLengthDescending.map(filterIsograms)
    // find = find the first item, if any, which satisfies the predicate
    val longestIsograms = isogramsByLengthDescending.find(_.nonEmpty)
    @tailrec def _indexesOf(word: String, from: Int, partialResult: ArrayBuffer[Int]): ArrayBuffer[Int] = {
      words.indexOf(word, from) match {
        case -1 => partialResult
        case i: Int =>
          partialResult += i
          _indexesOf(word, i + 1, partialResult)
      }
    }
    def indexesOf(word: String): ArrayBuffer[Int] = _indexesOf(word, 0, ArrayBuffer[Int]())
    longestIsograms match {
      case Some(isograms) =>
        Console.err.println("Message: done. Case-insensitive results for text inside <" + enclosingXMLTagName + "> tag:")
        isograms.toSet.foreach((isogram: String) => {
          val positions = indexesOf(isogram)
          val s = if (positions.length > 1) "s" else ""
          println(isogram + " (word" + s + " # " + positions.mkString(", ") + " in specified text)")
        })
      case None => Console.err.println("Message: done. No isograms in the text inside <" + enclosingXMLTagName + "> tag.")
    }
    sys.exit(0)
  }
}