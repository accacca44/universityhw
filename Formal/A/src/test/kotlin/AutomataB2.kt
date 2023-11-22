package test.kotlin

import main.kotlin.PDA
import java.io.File

fun main() {
    // aaabbb
    //aabbb
    //abab
    //
    //aaaabbbb
    //aaaaa

//    aabbc
//    aabbcc
//    aabccb
//    abc
//    aaaaaaabbcbcc

    val listb = listOf("aabbc", "aabbcc", "aabccb", "abc", "aaaaaaabbcbcc")
    val lista = listOf("aaabbb", "aabbb", "abab", "aaaabbbb", "aaaaa")

    val pda = PDA()
    pda.load(File("src/test/resources/form_I.B.2_b.txt"))
    for (word in listb) {
        val r = pda.matchWord(word)
        if (r != null) {
            println(r)
        } else {
            println("Not Accepted")
        }
    }
}