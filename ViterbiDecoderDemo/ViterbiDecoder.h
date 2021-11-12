/*
 *  ViterbiDecoder.h
 *
 *  Created on: May 29, 2021
 *      Author: Furkan
 */

#include <cstdint>
#ifndef INC_VITERBI_DECODER_H_
#define INC_VITERBI_DECODER_H_

void GetCodeVector(uint8_t* codeVector, uint8_t rate, uint8_t k);
void CreateInitialStatesMatrix(uint8_t* InitialStateMatrix, uint8_t k);
void CreateBranchMatrix(uint8_t* BranchMatrix, uint8_t* CodeVector, uint8_t rate, uint8_t k);
void BacktracePath(uint8_t* pathStates, uint8_t* receivedMessageBits, uint8_t numberOfMessageBits, uint8_t k, uint8_t truncationLength, uint16_t truncationIteration, uint8_t lastInfo);
void ViterbiDecode(uint8_t* codedMessageBits, uint8_t* receivedMessageBits, uint8_t* branchMatrix, uint8_t* initialStateMatrix, uint8_t numberOfMessageBits, uint8_t rate, uint8_t k, uint8_t truncationLength);

#endif /* INC_VITERBI_DECODER_H_ */