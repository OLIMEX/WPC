package number

import org.scalatest.FunSuite

import org.junit.runner.RunWith
import org.scalatest.junit.JUnitRunner

import number.roman._

@RunWith(classOf[JUnitRunner])
class RomanSuite extends FunSuite {

  test("one") {
    assert(roman.convert(1) === "I")
  }

  test("two") {
    assert(roman.convert(2) === "II")
  }

  test("three") {
    assert(roman.convert(3) === "III")
  }

  test("four") {
    assert(roman.convert(4) === "IV")
  }

  test("five") {
    assert(roman.convert(5) === "V")
  }

  test("six") {
    assert(roman.convert(6) === "VI")
  }

  test("eight") {
    assert(roman.convert(8) === "VIII")
  }

  test("ten") {
    assert(roman.convert(10) === "X")
  }

  test("fifty") {
    assert(roman.convert(50) === "L")
  }

  test("one hundred and eleven") {
    assert(roman.convert(111) === "CXI")
  }

  test("three thousand, nine hundred and ninty nine") {
    assert(roman.convert(3999) === "MMMCMXCIX")
  }

}