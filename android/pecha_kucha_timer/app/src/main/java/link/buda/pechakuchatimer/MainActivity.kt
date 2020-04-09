package link.buda.pechakuchatimer

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import java.util.*
import kotlin.concurrent.scheduleAtFixedRate

class MainActivity : AppCompatActivity() {

    companion object {
        private const val SLIDE_TIME = 20
    }

    private val timer = Timer("scheduler", true)
    private var counter = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        this.counter = SLIDE_TIME

        val resetButton = findViewById<Button>(R.id.reset_button)
        resetButton.setOnClickListener{
            this.counter = SLIDE_TIME
        }

        this.timer.scheduleAtFixedRate(0, 1000) {
            var timerView = findViewById<TextView>(R.id.timer)
            timerView.text = counter.toString()
            counter -= 1
            if (counter == 0) counter = SLIDE_TIME
        }
    }
}