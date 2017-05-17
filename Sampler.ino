/* #include <ArduinoJson.h> */
/* #include <string.h> */

/* const size_t INPUT_BUFFER_SIZE = 512; */
/* char input_buffer[INPUT_BUFFER_SIZE]; */

/* const size_t OUTPUT_BUFFER_SIZE = 512; */
/* char output_buffer[INPUT_BUFFER_SIZE]; */

/* bool run_time_exceeded[4]; */
/* bool active[4]; */
/* long start_time[4]; */
/* long prev_run_time[4]; */

/* bool first_command_recvd = false; */

/* long run_time = 10000; //ms */

/* /\* Pumps               RX   TX */
/*    pump0 uses Serial  (0    1) */
/*    pump1 uses serial1 (19   18) */
/*    pump2 uses serial2 (17   16) */
/*    pump3 uses serial3 (15   14) */
/*  *\/ */

/* /\* */
/*   possible json commands to handle */

/*   {'e':'0-4'} //enables 0-4 (turn on) */
/*   {'d':'0-4'} //disables 0-4 (turn off) */
/*   {'s':''} //stops all of them */
/*   {'t':'time'} //sets runtime in millis */
/* *\/ */
/* int handleCommand(char *buffer) */
/* { */
/*   char param; */
/*   char value[512]; //this has to be null terminated!! */
/*   sscanf(buffer,{"\"%c\":\"%s\""}); */

/*   if (param == 'e') */
/*     { */
/*       if (atoi(value) == 0) */
/*         { */
/*           enable(0); */
/*         } */
/*       if (atoi(value) == 1) */
/*         { */
/*           enable(1); */
/*         } */
/*       if (atoi(value) == 2) */
/*         { */
/*           enable(2); */
/*         } */
/*       if (atoi(value) == 3) */
/*         { */
/*           enable(3); */
/*         } */
/*     } */

/*   if (param == 'd') */
/*     { */
/*       if (atoi(value) == 0) */
/*         { */
/*           disable(0); */
/*         } */
/*       if (atoi(value) == 1) */
/*         { */
/*           disable(1); */
/*         } */
/*       if (atoi(value) == 2) */
/*         { */
/*           disable(2); */
/*         } */
/*       if (atoi(value) == 3) */
/*         { */
/*           disable(3); */
/*         } */
/*     } */
/*   if (param == 's') */
/*     { */
/*       stop(); */
/*     } */
/*   if (param == 't') //set pump runtime */
/*     { */
/*       run_time = atoi(value); //in milis!! */
/*     } */
/* } */
/* void setup() */
/* { */
/*   delay(1000); */
/*   Serial.begin(9600); //pump0 */
/*   Serial1.begin(9600); // */
/*   Serial2.begin(9600); */
/*   Serial3.begin(9600); */
  
/*   input_buffer[INPUT_BUFFER_SIZE] = '\0'; */
/*   output_buffer[OUTPUT_BUFFER_SIZE] = '\0'; */
/* } */
/* void loop() */
/* { */
/* } */
/* void enable(int pump) */
/* { */
/*   //send it c,0 */
/*   //will continuously run pump */
/*   //disables reporting (we dont care about this) */
/*     if (pump == 0) */
/*     { */
/*       Serial.print("C,0\r"); */
/*     } */
/*   if (pump == 1) */
/*     { */
/*       Serial1.print("C,0\r"); */
/*     } */
/*   if (pump == 2) */
/*     { */
/*       Serial2.print("C,0\r"); */
/*     } */
/*   if (pump == 3) */
/*     { */
/*       Serial3.print("C,0\r"); */
/*     } */

/* } */
/* void disable(int pump) */
/* { */
/*   //P pauses */
/*   if (pump == 0) */
/*     { */
/*       Serial.print("P\r"); */
/*     } */
/*   if (pump == 1) */
/*     { */
/*       Serial1.print("P\r"); */
/*     } */
/*   if (pump == 2) */
/*     { */
/*       Serial2.print("P\r"); */
/*     } */
/*   if (pump == 3) */
/*     { */
/*       Serial3.print("P\r"); */
/*     } */

/* } */
/* void stop() */
/* { */
/*   for (int i = 0; i < 4; i++) */
/*     { */
/*       disable(i); */
/*     } */
/* } */