
#include <Fuzzy.h>
Fuzzy *fuzzy = new Fuzzy();
void fuzzySetup() {

  FuzzyInput *temperature = new FuzzyInput(1);
  // Instantiating a FuzzySet object
  FuzzySet *cold_parameter  = new FuzzySet(-10,0,5,10);
  // Including the FuzzySet into FuzzyInput
  temperature->addFuzzySet(cold_parameter);
  // Instantiating a FuzzySet object
  FuzzySet *cool_parameter  = new FuzzySet(0,10,15,20);
  // Including the FuzzySet into FuzzyInput
  temperature->addFuzzySet(cool_parameter);
  // Instantiating a FuzzySet object
  FuzzySet *normal_parameter  = new FuzzySet(10,20,25,30);
  // Including the FuzzySet into FuzzyInput
  temperature->addFuzzySet(normal_parameter);
  FuzzySet *warm_parameter   = new FuzzySet(20,30,35,40);
  // Including the FuzzySet into FuzzyInput
  temperature->addFuzzySet(warm_parameter);
  FuzzySet *hot_parameter   = new FuzzySet(30,40,45,50);
  // Including the FuzzySet into FuzzyInput
  temperature->addFuzzySet(hot_parameter);
  // Including the FuzzyInput into Fuzzy
  fuzzy->addFuzzyInput(temperature);
  
  
  
   // Instantiating a FuzzyInput object
  FuzzyInput *soil_moisture = new FuzzyInput(2);
  // Instantiating a FuzzySet object
  FuzzySet *dry_parameter   = new FuzzySet(0,15,25,30);
  // Including the FuzzySet into FuzzyInput
  soil_moisture->addFuzzySet(dry_parameter);
  // Instantiating a FuzzySet object
  FuzzySet *moist_parameter   = new FuzzySet(25,40,50,75);
  // Including the FuzzySet into FuzzyInput
  soil_moisture->addFuzzySet(moist_parameter);
  // Instantiating a FuzzySet object
  FuzzySet *wet_parameter   = new FuzzySet(50,60,75,100);
  // Including the FuzzySet into FuzzyInput
  soil_moisture->addFuzzySet(wet_parameter);
  // Including the FuzzyInput into Fuzzy
  fuzzy->addFuzzyInput(soil_moisture);
  
  
  
  
  
  
  // Instantiating a FuzzyOutput objects
  FuzzyOutput *sprinkler_duration = new FuzzyOutput(1);
  // Instantiating a FuzzySet object
  FuzzySet *short_parameter  = new FuzzySet(0,2,3,5);
  // Including the FuzzySet into FuzzyOutput
  sprinkler_duration->addFuzzySet(short_parameter );
  // Instantiating a FuzzySet object
  FuzzySet *medium_parameter  = new FuzzySet(4,6,8,9);
  // Including the FuzzySet into FuzzyOutput
  sprinkler_duration->addFuzzySet(medium_parameter );
  // Instantiating a FuzzySet object
  FuzzySet *long_parameter  = new FuzzySet(7,10,12,15);
  // Including the FuzzySet into FuzzyOutput
  sprinkler_duration->addFuzzySet(long_parameter );
  // Including the FuzzyOutput into Fuzzy
  fuzzy->addFuzzyOutput(sprinkler_duration);
  
  
  //fuzzy rule 1
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityDryAndTemperatureCold = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityDryAndTemperatureCold->joinWithAND(dry_parameter, cold_parameter);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenSprinklerShort = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenSprinklerShort->addOutput(short_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1, humidityDryAndTemperatureCold, thenSprinklerShort);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule01);
  
  //fuzzy rule 2
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityDryAndTemperatureCool = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityDryAndTemperatureCool->joinWithAND(dry_parameter, cool_parameter);
  // Instantiating a FuzzyRuleConsequent objects
//  FuzzyRuleConsequent *thenSprinklerShort = new FuzzyRuleConsequent();
//  // Including a FuzzySet to this FuzzyRuleConsequent
//  thenSprinklerShort->addOutput(short_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2, humidityDryAndTemperatureCool, thenSprinklerShort);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule02);
  
  
  //fuzzy rule 3
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityDryAndTemperatureNormal = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityDryAndTemperatureNormal->joinWithAND(dry_parameter, normal_parameter);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenSprinklerMedium = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenSprinklerMedium->addOutput(medium_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule03 = new FuzzyRule(3, humidityDryAndTemperatureNormal, thenSprinklerMedium);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule03);
  
  
  //fuzzy rule 4
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityDryAndTemperatureWarm = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityDryAndTemperatureWarm->joinWithAND(dry_parameter, warm_parameter);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenSprinklerLong = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenSprinklerLong->addOutput(long_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule04 = new FuzzyRule(4, humidityDryAndTemperatureWarm, thenSprinklerLong);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule04);
  
  
  //fuzzy rule 5
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityDryAndTemperatureHot = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityDryAndTemperatureHot->joinWithAND(dry_parameter, hot_parameter);
  // Instantiating a FuzzyRuleConsequent objects
//  FuzzyRuleConsequent *thenSprinklerLong = new FuzzyRuleConsequent();
//  // Including a FuzzySet to this FuzzyRuleConsequent
//  thenSprinklerLong->addOutput(long_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule05 = new FuzzyRule(5, humidityDryAndTemperatureHot, thenSprinklerLong);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule05);
  
  
  //fuzzy rule 6
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityMoistAndTemperatureCold = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityMoistAndTemperatureCold->joinWithAND(moist_parameter, cold_parameter);
  // Instantiating a FuzzyRuleConsequent objects
//  FuzzyRuleConsequent *thenSprinklerShort = new FuzzyRuleConsequent();
//  // Including a FuzzySet to this FuzzyRuleConsequent
//  thenSprinklerShort->addOutput(short_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule06 = new FuzzyRule(6, humidityMoistAndTemperatureCold, thenSprinklerShort);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule06);
  
   //fuzzy rule 7
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityMoistAndTemperatureCool = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityMoistAndTemperatureCool->joinWithAND(moist_parameter, cool_parameter);
  // Instantiating a FuzzyRuleConsequent objects
//  FuzzyRuleConsequent *thenSprinklerShort = new FuzzyRuleConsequent();
//  // Including a FuzzySet to this FuzzyRuleConsequent
//  thenSprinklerShort->addOutput(short_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule07 = new FuzzyRule(7, humidityMoistAndTemperatureCool, thenSprinklerShort);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule07);
  
  
   //fuzzy rule 8
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityMoistAndTemperatureNormal = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityMoistAndTemperatureNormal->joinWithAND(moist_parameter, normal_parameter);
  // Instantiating a FuzzyRuleConsequent objects
//  FuzzyRuleConsequent *thenSprinklerMedium = new FuzzyRuleConsequent();
//  // Including a FuzzySet to this FuzzyRuleConsequent
//  thenSprinklerMedium->addOutput(medium_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule08 = new FuzzyRule(8, humidityMoistAndTemperatureNormal, thenSprinklerMedium);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule08);
  
  
  //fuzzy rule 9
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityMoistAndTemperatureWarm = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityMoistAndTemperatureWarm->joinWithAND(moist_parameter, warm_parameter);
  // Instantiating a FuzzyRuleConsequent objects
//  FuzzyRuleConsequent *thenSprinklerMedium = new FuzzyRuleConsequent();
//  // Including a FuzzySet to this FuzzyRuleConsequent
//  thenSprinklerMedium->addOutput(medium_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule09 = new FuzzyRule(9, humidityMoistAndTemperatureWarm, thenSprinklerMedium);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule09);
  
  
  
    //fuzzy rule 10
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityMoistAndTemperatureHot = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityMoistAndTemperatureHot->joinWithAND(moist_parameter, hot_parameter);
  // Instantiating a FuzzyRuleConsequent objects
//  FuzzyRuleConsequent *thenSprinklerLong = new FuzzyRuleConsequent();
//  // Including a FuzzySet to this FuzzyRuleConsequent
//  thenSprinklerLong->addOutput(long_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule10 = new FuzzyRule(10, humidityMoistAndTemperatureHot, thenSprinklerLong);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule10);
  
  
  
  //fuzzy rule 11
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityWetAndTemperatureCold = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityWetAndTemperatureCold->joinWithAND(wet_parameter, cold_parameter);
  // Instantiating a FuzzyRuleConsequent objects
//  FuzzyRuleConsequent *thenSprinklerShort = new FuzzyRuleConsequent();
//  // Including a FuzzySet to this FuzzyRuleConsequent
//  thenSprinklerShort->addOutput(short_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule11 = new FuzzyRule(11, humidityWetAndTemperatureCold, thenSprinklerShort);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule11);
  
  
  //fuzzy rule 12
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityWetAndTemperatureCool = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityWetAndTemperatureCool->joinWithAND(wet_parameter, cool_parameter);
  // Instantiating a FuzzyRuleConsequent objects
//  FuzzyRuleConsequent *thenSprinklerShort = new FuzzyRuleConsequent();
//  // Including a FuzzySet to this FuzzyRuleConsequent
//  thenSprinklerShort->addOutput(short_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule12 = new FuzzyRule(12, humidityWetAndTemperatureCool, thenSprinklerShort);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule12);
  
  
  //fuzzy rule 13
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityWetAndTemperatureNormal = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityWetAndTemperatureNormal->joinWithAND(wet_parameter, normal_parameter);
  // Instantiating a FuzzyRuleConsequent objects
//  FuzzyRuleConsequent *thenSprinklerShort1 = new FuzzyRuleConsequent();
//  // Including a FuzzySet to this FuzzyRuleConsequent
//  thenSprinklerShort->addOutput(short_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule13 = new FuzzyRule(13, humidityWetAndTemperatureNormal, thenSprinklerShort);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule13);
  
 
  //fuzzy rule 14
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityWetAndTemperatureWarm = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityWetAndTemperatureWarm->joinWithAND(wet_parameter, warm_parameter);
  // Instantiating a FuzzyRuleConsequent objects
//  FuzzyRuleConsequent *thenSprinklerMedium = new FuzzyRuleConsequent();
//  // Including a FuzzySet to this FuzzyRuleConsequent
//  thenSprinklerMedium->addOutput(medium_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule14 = new FuzzyRule(14, humidityWetAndTemperatureWarm, thenSprinklerMedium);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule14);
  
  
  //fuzzy rule 15
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *humidityWetAndTemperatureHot = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  humidityWetAndTemperatureHot->joinWithAND(wet_parameter, hot_parameter);
  // Instantiating a FuzzyRuleConsequent objects
//  FuzzyRuleConsequent *thenSprinklerLong = new FuzzyRuleConsequent();
//  // Including a FuzzySet to this FuzzyRuleConsequent
//  thenSprinklerLong->addOutput(long_parameter);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule15 = new FuzzyRule(15, humidityWetAndTemperatureHot, thenSprinklerLong);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule15);
}

float fuzzyDecission(int soil_moisture, float temperature) {
  fuzzy->setInput(1,temperature);
  fuzzy->setInput(2,soil_moisture);
  fuzzy->fuzzify();
  return fuzzy->defuzzify(1);
}
