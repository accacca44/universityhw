package test.kotlin

import main.kotlin.NewStateMachine
import java.io.File

fun main() {
    val sm1 = NewStateMachine(File("src/test/resources/form_I.A.3.txt"))
    val sm2 = sm1.eliminateNonProductiveStates().eliminateUnreachableStates()
    sm2.generateDotCode()
}