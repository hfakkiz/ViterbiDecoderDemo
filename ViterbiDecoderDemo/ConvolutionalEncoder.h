/*
 *  ConvolutionalEncoder.h
 *
 *  Created on: 23 May 2021
 *      Author: Furkan
 */

#include <cstdint>
#ifndef INC_CONVOLUTIONAL_ENCODER_H_
#define INC_CONVOLUTIONAL_ENCODER_H_

void GetCodeVector(uint8_t* codeVector, uint8_t rate, uint8_t k);
void ConvolutionalEncode(uint8_t* messageBits, uint8_t* codedMessageBits, uint8_t numberOfMessageBits, uint8_t rate, uint8_t k, uint8_t* codeVector);

#endif /* INC_CONVOLUTIONAL_ENCODER_H_ */
