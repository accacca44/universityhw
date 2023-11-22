package test.kotlin

import main.kotlin.NewStateMachine
import java.io.File

fun main() {
    val sm1 = NewStateMachine(File("src/test/resources/form_I.B.3_b.txt"))
    sm1.generateDotCode()
//    sm1.minimal()
}