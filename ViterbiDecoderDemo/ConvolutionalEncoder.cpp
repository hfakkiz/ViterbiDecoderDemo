/*
 * convolutional_encoder.c
 *
 *  Created on: 23 May 2021
 *      Author: Furkan
 */

#include "ConvolutionalEncoder.h"
#include <cstdint>

void GetCodeVector(uint8_t* codeVector, uint8_t rate, uint8_t k)
{
	uint8_t codeVector_r2_k3[2][3] = { {1, 1, 1}, {1, 0, 1} };
	uint8_t codeVector_r2_k4[2][4] = { {1, 1, 1, 1}, {1, 0, 1, 1} };
	uint8_t codeVector_r2_k5[2][5] = { {1, 0, 1, 1, 1}, {1, 1, 0, 0, 1} };
	uint8_t codeVector_r2_k6[2][6] = { {1, 0, 1, 1, 1, 1}, {1, 1, 0, 1, 0, 1} };
	uint8_t codeVector_r2_k7[2][7] = { {1, 0, 0, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 0, 1} };
	uint8_t codeVector_r2_k8[2][8] = { {1, 0, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 0, 1, 0, 1} };
	uint8_t codeVector_r2_k9[2][9] = { {1, 1, 0, 1, 0, 1, 1, 1, 1}, {1, 0, 0, 0, 1, 1, 1, 0, 1} };

	uint8_t codeVector_r3_k3[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 0, 1} };
	uint8_t codeVector_r3_k4[3][4] = { {1, 1, 1, 1}, {1, 0, 1, 1}, {1, 1, 0, 1} };
	uint8_t codeVector_r3_k5[3][5] = { {1, 1, 1, 1, 1}, {1, 1, 0, 1, 1}, {1, 0, 1, 0, 1} };
	uint8_t codeVector_r3_k6[3][6] = { {1, 0, 1, 1, 1, 1}, {1, 1, 0, 1, 0, 1}, {1, 1, 1, 0, 0, 1} };
	uint8_t codeVector_r3_k7[3][7] = { {1, 0, 0, 1, 1, 1, 1}, {1, 0, 1, 0, 1, 1, 1}, {1, 1, 0, 1, 1, 0, 1} };
	uint8_t codeVector_r3_k8[3][8] = { {1, 1, 1, 0, 1, 1, 1, 1}, {1, 0, 0, 1, 1, 0, 1, 1}, {1, 0, 1, 0, 1, 0, 0, 1} };

	for (uint8_t i = 0; i < rate; i++)
	{
		for (uint8_t j = 0; j < k; j++)
		{
			switch (k)
			{
			case 3:
				if (rate == 2)
				{
					*codeVector = codeVector_r2_k3[i][j];
					codeVector++;
				}
				else if (rate == 3)
				{
					*codeVector = codeVector_r3_k3[i][j];
					codeVector++;
				}
				break;
			case 4:
				if (rate == 2)
				{
					*codeVector = codeVector_r2_k4[i][j];
					codeVector++;
				}
				else if (rate == 3)
				{
					*codeVector = codeVector_r3_k4[i][j];
					codeVector++;
				}
				break;
			case 5:
				if (rate == 2)
				{
					*codeVector = codeVector_r2_k5[i][j];
					codeVector++;
				}
				else if (rate == 3)
				{
					*codeVector = codeVector_r3_k5[i][j];
					codeVector++;
				}
				break;
			case 6:
				if (rate == 2)
				{
					*codeVector = codeVector_r2_k6[i][j];
					codeVector++;
				}
				else if (rate == 3)
				{
					*codeVector = codeVector_r3_k6[i][j];
					codeVector++;
				}
				break;
			case 7:
				if (rate == 2)
				{
					*codeVector = codeVector_r2_k7[i][j];
					codeVector++;
				}
				else if (rate == 3)
				{
					*codeVector = codeVector_r3_k7[i][j];
					codeVector++;
				}
				break;
			case 8:
				if (rate == 2)
				{
					*codeVector = codeVector_r2_k8[i][j];
					codeVector++;
				}
				else if (rate == 3)
				{
					*codeVector = codeVector_r3_k8[i][j];
					codeVector++;
				}
				break;
			case 9:
				if (rate == 2)
				{
					*codeVector = codeVector_r2_k9[i][j];
					codeVector++;
				}
				break;
			}
		}
	}
}


void ConvolutionalEncode(uint8_t* messageBits, uint8_t* codedMessageBits, uint8_t numberOfMessageBits, uint8_t rate, uint8_t k, uint8_t* codeVector)
{
	uint8_t output[3];
	uint8_t block[9];

	for (uint8_t i = 0; i < k; i++)
		block[i] = 0;

	for (uint8_t i = 0; i < numberOfMessageBits; i++)
	{
		for (uint8_t j = 1; j <= k; j++)
		{
			if (j == k)
			{
				block[k - j] = *(messageBits + i);
				continue;
			}
			else
			{
				block[k - j] = block[k - j - 1];
			}
		}

		for (uint8_t m = 0; m < rate; m++)
		{
			output[m] = 0;

			for (uint8_t n = 0; n < k; n++)
				output[m] += *((codeVector + m * k) + n) * block[n];

			output[m] = output[m] % 2;

			*codedMessageBits = output[m];
			codedMessageBits++;
		}
	}
}

