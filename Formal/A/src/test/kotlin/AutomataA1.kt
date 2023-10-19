package test.kotlin

import java.io.File

fun main(){
    val outFile = File("src/test/out/out1.txt")
    StateMachine.loadStates("src/main/resources/form_I.A.1.txt")
    val txt = StateMachine.generateDotCode()
    println(txt)
    outFile.writeText(txt)
}