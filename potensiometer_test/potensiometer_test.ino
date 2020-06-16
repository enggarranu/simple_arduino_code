int val_pot; //variable to store the analog value read
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); ////sets the baud rate of the UART for serial transmission
}

// put your main code here, to run repeatedly:
void loop() {

  //reads the analog value of pin A0 connected to the potentiometer
  val_pot = analogRead(A1);
  //print out the following string
  Serial.print("The digital value is: ");
  //print out the value you read on the serial monitor
  Serial.println(val_pot);
  //Wait 10 ms for the next reading.
  delay(100);
}
