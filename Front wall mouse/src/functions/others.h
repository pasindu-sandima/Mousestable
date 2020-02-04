void Buzzer(uint16_t time_delay){
    digitalWrite(Buzzer_Pin,HIGH);
    delay(time_delay);
    digitalWrite(Buzzer_Pin,LOW);
}

void init_hardware_timer_version(void){
 RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;
 RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; //AFIO might not even be needed?
 RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //AFIO might not even be needed?

 //GPIO must be input floating which is default so no code to write for that

 // value to count up to : 16 bit so max is 0xFFFF = 65535
 TIM2->ARR = 0xFFFF;
 TIM3->ARR = 0xFFFF;


 //per datasheet instructions
 TIM2->CCMR1 |= (TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0 );  //step 1 and 2
 TIM2->CCER |= (TIM_CCER_CC1P);  // step 3 and 4
 TIM2->CCER &= ~(TIM_CCER_CC2P);  // step 3 and 4
 TIM2->SMCR |= (TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0 );   //step 5
 TIM2->CR1 |= TIM_CR1_CEN ;     //step 6


  //per datasheet instructions
 TIM3->CCMR1 |= (TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0 );  //step 1 and 2
 TIM3->CCER |= (TIM_CCER_CC1P);  // step 3 and 4
 TIM3->CCER &= ~(TIM_CCER_CC2P);  // step 3 and 4
 TIM3->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;   //step 5
 TIM3->CR1 |= TIM_CR1_CEN ;     //step 6
}