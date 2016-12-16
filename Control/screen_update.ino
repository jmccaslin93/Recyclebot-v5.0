//Screen Updates
void screenUpdate(int state, double currentTemp) {
  
  lastInputTime = millis(); 
  lcd.setCursor(0,1);
  lcd.clear();
  
  auger.runSpeed();
  puller.runSpeed();
  winder.runSpeed();
  
  switch (state) {
    case 0 :
      infoScreen(currentTemp);
      break;
    case 1 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Manual");
      break;
    case 2 :
      lcd.print("-> Manual");
      lcd.setCursor(0,1);
      lcd.print("Auto");
      break;
    case 3 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Cooling");
      break;
    case 4 :
      lcd.print("-> Cooling");
      lcd.setCursor(0,1);
      lcd.print("Servo");
      break;
    case 5 :
      lcd.print("-> Fan");
      lcd.setCursor(0,1);
      lcd.print("Water Bath");
      break;
    case 6 :
      lcd.print("-> Fan Power");
      lcd.setCursor(0,1);
      lcd.print("Speed");
      break;
    case 7 :
      lcd.print("-> On");
      lcd.setCursor(0,1);
      lcd.print("Off");
      break;
    case 8 :
      lcd.print("-> Off");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 9 :
      lcd.print("-> Speed");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 10 :
      lcd.print("-> Water Bath");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 11 :
      lcd.print("-> Bath Power");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 12 :
      lcd.print("-> On");
      lcd.setCursor(0,1);
      lcd.print("Off");
      break;
    case 13 :
      lcd.print("-> Off");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 14 :
      lcd.print("-> Servo");
      lcd.setCursor(0,1);
      lcd.print("Puller");
      break;
    case 15 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Spool Width");
      break;
    case 16 :
      lcd.print("-> Spool Width");
      lcd.setCursor(0,1);
      lcd.print("Position");
      break;
    case 17 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Start");
      break;
    case 18 :
      lcd.print("-> Start");
      lcd.setCursor(0,1);
      lcd.print("Stop");
      break;
    case 19 :
      lcd.print("-> Stop");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 20 :
      lcd.print("-> Position");
      lcd.setCursor(0,1);
      lcd.print("Step Size");
      break;
    case 21 :
      lcd.print("-> Step Size");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 22 :
      lcd.print("-> Puller");
      lcd.setCursor(0,1);
      lcd.print("Auger");
      break;
    case 23 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Puller Power");
      break;
    case 24 :
      lcd.print("-> PullerPower");
      lcd.setCursor(0,1);
      lcd.print("Puller Speed");
      break;
    case 25 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("On");
      break;
    case 26 :
      lcd.print("-> On");
      lcd.setCursor(0,1);
      lcd.print("Off");
      break;
    case 27 :
      lcd.print("-> Off");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 28 :
      lcd.print("-> Auger");
      lcd.setCursor(0,1);
      lcd.print("Winder");
      break;
    case 29 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Auger Power");
      break;
    case 30 :
      lcd.print("-> Auger Power");
      lcd.setCursor(0,1);
      lcd.print("Speed");
      break;
    case 31 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("On");
      break;
    case 32 :
      lcd.print("-> On");
      lcd.setCursor(0,1);
      lcd.print("Off");
      break;
    case 33 :
      lcd.print("-> Off");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 34 :
      lcd.print("-> Speed");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 35 :
      lcd.print("-> Winder");
      lcd.setCursor(0,1);
      lcd.print("Heater");
      break;
    case 36 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Winder Power");
      break;
    case 37 :
      lcd.print("-> Winder Power");
      lcd.setCursor(0,1);
      lcd.print("Speed");
      break;
    case 38 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("On");
      break;
    case 39 :
      lcd.print("-> On");
      lcd.setCursor(0,1);
      lcd.print("Off");
      break;
    case 40 :
      lcd.print("-> Off");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 41 :
      lcd.print("-> Speed");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 42 :
      lcd.print("-> Heater");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 43 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Heater Power");
      break;
    case 44 :
      lcd.print("-> Heater Power");
      lcd.setCursor(0,1);
      lcd.print("Temperature");
      break;
    case 45 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("On");
      break;
    case 46 :
      lcd.print("-> On");
      lcd.setCursor(0,1);
      lcd.print("Off");
      break;
    case 47 :
      lcd.print("-> Off");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 48 :
      lcd.print("-> Temperature");
      lcd.setCursor(0,1);
      lcd.print("Back");
      
      break;
    case 49 :
      lcd.print("-> Auto");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 50 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Plastic Type");
      break;
    case 51 :
      lcd.print("-> Plastic Type");
      lcd.setCursor(0,1);
      lcd.print("Diameter");
      break;
    case 52 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Regular PLA");
      break;
    case 53 :
      lcd.print("-> Regular PLA");
      lcd.setCursor(0,1);
      lcd.print("Recycled PLA");
      break;
    case 54 :
      lcd.print("-> Recycled PLA");
      lcd.setCursor(0,1);
      lcd.print("Recycled ABS");
      break;
    case 55 :
      lcd.print("-> Recycled ABS");
      lcd.setCursor(0,1);
      lcd.print("Recycled TPE");
      break;
    case 56 :
      lcd.print("-> Recycled TPE");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 57 :
      lcd.print("-> Diameter");
      lcd.setCursor(0,1);
      lcd.print("Spool Width");
      break;
    case 58 :
      lcd.print("-> Spool Width");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 59 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Start");
      break;
    case 60 :
      lcd.print("-> Start");
      lcd.setCursor(0,1);
      lcd.print("Stop");
      break;
    case 61 :
      lcd.print("-> Stop");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case 62 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Fan");
      break;
    case 63 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Fan Power");
      break;
    case 64 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("On");
      break;
    case 65 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("Bath Power");
      break;
    case 66 :
      lcd.print("-> Back");
      lcd.setCursor(0,1);
      lcd.print("On");
      break;
    case 67 :
      lcd.print("Fan Speed");
      lcd.setCursor(0,1);
       lcd.print(encoderPos);
       lcd.print(" %");
     break;
    case 68 :
      lcd.print("Spool Start pos");
        lcd.setCursor(0,1);
        lcd.print(encoderPos);
        filamentGuide.write(encoderPos);
      break;
    case (69) :
      lcd.print("Spool Stop Pos");
      lcd.setCursor(0,1);
      lcd.print(encoderPos);
     filamentGuide.write(encoderPos);
     break;
    case (70) :
      lcd.print("Servo Position");
      lcd.setCursor(0,1);
      lcd.print(encoderPos);
      
      filamentGuide.write(encoderPos);
      break;
    case (71) :
      lcd.print("-> Back");
      lcd.print("1.75 mm");
      break;
    case (72) :
      lcd.print("-> 1.75 mm");
      lcd.print("3.0 mm");
      break;
    case (73) :
      lcd.print("-> 3.0 mm");
      lcd.print("Back");
    case (74) :
      lcd.print("Auger Speed");
      
      lcd.setCursor(0,1);
      
      lcd.print(encoderPos);
      lcd.print(" RPM");
      break;
    case (75) :
      lcd.print("Winder Speed");
      lcd.print(encoderPos);
      lcd.print(" RPM");
      break;
    case (76) :
      lcd.print("Heater Temp");
      lcd.setCursor(0,1);
      lcd.print(encoderPos);
      lcd.print(" C");
      break;
    case (77) :
      lcd.print("-> Puller Speed");
      lcd.setCursor(0,1);
      lcd.print("Back");
      break;
    case (78) :
      lcd.print("Puller Speed");
      lcd.setCursor(0,1);
      lcd.print(encoderPos);
      lcd.print(" RPM");
      break;
  }
    auger.runSpeed();
  puller.runSpeed();
  winder.runSpeed();
   
}






void infoScreen(double currentTemp) {
  
  auger.runSpeed();
  puller.runSpeed();
  winder.runSpeed();
  
  if (mode == 1) { //possibly add motor run fuctions
    
    lcd.print("Auto ");
    lcd.print(currentDiameter);
    lcd.print("/");
    lcd.print(desiredDiameter);
    lcd.print("mm");
    lcd.setCursor(0,1);
    lcd.print("A_RPM=");
    
    lcd.print(currentAugerRPM);
    lcd.print(currentTemp);
    lcd.print("/");
    lcd.print(desiredTemp);
    lcd.print(" C");

  }
  else {
    lcd.print("Manual ");
    lcd.print(currentDiameter);
    lcd.print(" mm");
    lcd.setCursor(0,1);
    lcd.print(currentTemp);
    lcd.print("/");
    lcd.print(desiredTemp);
    lcd.print(" C");
  }
  directory = 0;
  
  auger.runSpeed();
  puller.runSpeed();
  winder.runSpeed();

}
