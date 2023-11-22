package test.kotlin

import StateMachine
import main.kotlin.NewStateMachine
import java.io.File

fun main(){
    val inputFile = File("src/test/resources/form_I.A.3.txt")
    val sm1 = NewStateMachine(inputFile)
    sm1.generateDotCode()
}