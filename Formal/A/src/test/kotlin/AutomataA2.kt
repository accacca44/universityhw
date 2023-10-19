package test.kotlin

import State
import StateMachine
import java.io.File

fun main() {
    val inputFileName = "src/main/resources/form_I.A.2.txt"
    val outputFileName = "src/test/out/out2.txt"
    val outputFile = File(outputFileName)

    val aut = StateMachine.generateAutomataFrom(inputFileName)
    outputFile.writeText(aut)

    StateMachine.loadStates(outputFileName)
    val txt = StateMachine.generateDotCode()
    println(txt)
}