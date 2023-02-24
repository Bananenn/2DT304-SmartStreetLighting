# 2dt304 Smart streetlighting project

## By
* André Franzén, af223kr
* David valtonen, de222hh

## Original project prposal 
### 1 Project Idea

The goal of the project is to contribute to a more sustainable and safe society by enhancing the ability of street lighting. Instead of the street lights always being powered on they should be regulated on demand. A system will be constructed so that streetlights can be dimmed when they are not needed. The concept may also be elaborated on and be used to warn road users of something being in the way or that there is oncoming traffic. 


### 2 Background, Motivation and Proposal

Street Lighting uses a substantial amount of electricity according to SCB () Street lighting uses approximately 1,5 TWh [1] per year. This project aims to implement a solution that could lead to a real-world system that could lower this power usage without affecting safety. This will be achieved by making street lighting smart. A sensor will notice if a car or pedestrian is near and the brightness will be adjusted accordingly. Energy consumption and safety are two subjects that are very relevant in society. This project seeks to improve both of those subjects. The system will also be able to warn of potential dangers with the use of the same sensors. 








lampor_tända_till = 0
tid_Nu = 0

Pir_Aktiverad {
  //Uppdatera tiden då lamporna ska vara tända
  lampor_tända_till = tid_Nu + 5s
}

//Annan loop som hela tiden körs 
lamp_loop {
  if (lampor_tända_till > tid_Nu) {
    lampout = HIGH
  } else {
    lampout = LOW
  }
}
