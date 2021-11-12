/*
 * viterbi_decoder.c
 *
 *  Created on: May 29, 2021
 *      Author: Furkan
 */

#include "math.h"
#include "ViterbiDecoder.h"
#include <cstdint>

void GetCodeVector(uint8_t* CodeVector, uint8_t rate, uint8_t k)
{
    uint8_t CodeVector_r2_k3[2][3] = { {1, 1, 1}, {1, 0, 1} };
    uint8_t CodeVector_r2_k4[2][4] = { {1, 1, 1, 1}, {1, 0, 1, 1} };
    uint8_t CodeVector_r2_k5[2][5] = { {1, 0, 1, 1, 1}, {1, 1, 0, 0, 1} };
    uint8_t CodeVector_r2_k6[2][6] = { {1, 0, 1, 1, 1, 1}, {1, 1, 0, 1, 0, 1} };
    uint8_t CodeVector_r2_k7[2][7] = { {1, 0, 0, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 0, 1} };
    uint8_t CodeVector_r2_k8[2][8] = { {1, 0, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 0, 1, 0, 1} };
    uint8_t CodeVector_r2_k9[2][9] = { {1, 1, 0, 1, 0, 1, 1, 1, 1}, {1, 0, 0, 0, 1, 1, 1, 0, 1} };

    uint8_t CodeVector_r3_k3[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 0, 1} };
    uint8_t CodeVector_r3_k4[3][4] = { {1, 1, 1, 1}, {1, 0, 1, 1}, {1, 1, 0, 1} };
    uint8_t CodeVector_r3_k5[3][5] = { {1, 1, 1, 1, 1}, {1, 1, 0, 1, 1}, {1, 0, 1, 0, 1} };
    uint8_t CodeVector_r3_k6[3][6] = { {1, 0, 1, 1, 1, 1}, {1, 1, 0, 1, 0, 1}, {1, 1, 1, 0, 0, 1} };
    uint8_t CodeVector_r3_k7[3][7] = { {1, 0, 0, 1, 1, 1, 1}, {1, 0, 1, 0, 1, 1, 1}, {1, 1, 0, 1, 1, 0, 1} };
    uint8_t CodeVector_r3_k8[3][8] = { {1, 1, 1, 0, 1, 1, 1, 1}, {1, 0, 0, 1, 1, 0, 1, 1}, {1, 0, 1, 0, 1, 0, 0, 1} };

    for (uint8_t i = 0; i < rate; i++)
    {
        for (uint8_t j = 0; j < k; j++)
        {
            switch (k)
            {
            case 3:
                if (rate == 2)
                {
                    *CodeVector = CodeVector_r2_k3[i][j];
                    CodeVector++;
                }
                else if (rate == 3)
                {
                    *CodeVector = CodeVector_r3_k3[i][j];
                    CodeVector++;
                }
                break;
            case 4:
                if (rate == 2)
                {
                    *CodeVector = CodeVector_r2_k4[i][j];
                    CodeVector++;
                }
                else if (rate == 3)
                {
                    *CodeVector = CodeVector_r3_k4[i][j];
                    CodeVector++;
                }
                break;
            case 5:
                if (rate == 2)
                {
                    *CodeVector = CodeVector_r2_k5[i][j];
                    CodeVector++;
                }
                else if (rate == 3)
                {
                    *CodeVector = CodeVector_r3_k5[i][j];
                    CodeVector++;
                }
                break;
            case 6:
                if (rate == 2)
                {
                    *CodeVector = CodeVector_r2_k6[i][j];
                    CodeVector++;
                }
                else if (rate == 3)
                {
                    *CodeVector = CodeVector_r3_k6[i][j];
                    CodeVector++;
                }
                break;
            case 7:
                if (rate == 2)
                {
                    *CodeVector = CodeVector_r2_k7[i][j];
                    CodeVector++;
                }
                else if (rate == 3)
                {
                    *CodeVector = CodeVector_r3_k7[i][j];
                    CodeVector++;
                }
                break;
            case 8:
                if (rate == 2)
                {
                    *CodeVector = CodeVector_r2_k8[i][j];
                    CodeVector++;
                }
                else if (rate == 3)
                {
                    *CodeVector = CodeVector_r3_k8[i][j];
                    CodeVector++;
                }
                break;
            case 9:
                if (rate == 2)
                {
                    *CodeVector = CodeVector_r2_k9[i][j];
                    CodeVector++;
                }
                break;
            }
        }
    }
}

void CreateInitialStatesMatrix(uint8_t* InitialStateMatrix, uint8_t k)
{
    uint16_t NumberOfState = (uint16_t)pow(2, k - 1), counter = 0;
    uint8_t tempInitialStateMatrix[2 * NumberOfState][k + 1];

    for (uint16_t i = 0; i < 2 * NumberOfState; i++)
    {
        if (i % 2 == 0)
            counter++;

        tempInitialStateMatrix[i][k] = counter;

        if (i < NumberOfState)
            tempInitialStateMatrix[i][k - 1] = i + 1;
        else
            tempInitialStateMatrix[i][k - 1] = i + 1 - NumberOfState;
    }

    for (uint16_t i = 0; i < 2 * NumberOfState; i++)
    {
        for (uint8_t j = k - 2; j >= 0; j--)
        {
            if (j > 7)
                break;

            tempInitialStateMatrix[i][j] = (2 * tempInitialStateMatrix[i][j + 1] - 1) % NumberOfState;
        }
    }

    for (uint16_t i = 0; i < 2 * NumberOfState; i++)
    {
        for (uint8_t j = 0; j < k + 1; j++)
        {
            *InitialStateMatrix = tempInitialStateMatrix[i][j];
            InitialStateMatrix++;
        }
    }
}

void CreateBranchMatrix(uint8_t* BranchMatrix, uint8_t* CodeVector, uint8_t rate, uint8_t k)
{
    uint8_t output = 0;
    uint16_t NumberOfState = (uint16_t)pow(2, k - 1);
    uint8_t* tempCodeVector = CodeVector;
    uint8_t BinaryMatrix[NumberOfState][k];

    for (uint8_t j = k - 1; j > 0; j--)
    {
        if (j > 7)
            break;

        for (uint16_t i = 0; i < NumberOfState; i++)
        {
            if (i % (uint16_t)pow(2, k - j) < (uint16_t)pow(2, (k - 1) - j))
                BinaryMatrix[i][j] = 0;
            else
                BinaryMatrix[i][j] = 1;
        }
    }

    for (uint16_t i = 0; i < NumberOfState; i++)
    {
        for (uint8_t j = 0; j < 2; j++)
        {
            BinaryMatrix[i][0] = j;
            tempCodeVector = CodeVector;

            for (uint8_t m = 0; m < rate; m++)
            {
                output = 0;

                for (uint8_t n = 0; n < k; n++)
                {
                    output = output + (*tempCodeVector * BinaryMatrix[i][n]);
                    tempCodeVector++;
                }

                output = output % 2;

                *BranchMatrix = output;
                BranchMatrix++;
            }
        }
    }
}


void ViterbiDecode(uint8_t* codedMessageBits, uint8_t* receivedMessageBits, uint8_t* branchMatrix, uint8_t* initialStateMatrix, uint8_t numberOfMessageBits, uint8_t rate, uint8_t k, uint8_t truncationLength)
{
    uint16_t iteration = 0;
    uint16_t numberOfState = (uint16_t)pow(2, k - 1);
    uint16_t numberOfBranch = (uint16_t)pow(2, k);
    uint8_t minimumPathError = rate * numberOfMessageBits;
    uint8_t selectedPath, truncationIteration = 1;

    if (truncationLength == 0)
        truncationLength = numberOfMessageBits;

    uint8_t pathError[numberOfBranch];

    uint8_t pathStateError[numberOfState];
    uint8_t tempPathStateError[numberOfState];

    uint8_t pathState[numberOfState][truncationLength + 1];
    uint8_t tempPathState[numberOfState][truncationLength + 1];

    for (uint8_t i = 0; i < rate * numberOfMessageBits; i++)
    {
        if ((i - 1) % rate == rate - 1)
            iteration++;

        if (i < (k - 1) * rate)
        {
            if (i < rate)
            {
                for (uint8_t j = 0; j < 2; j++)
                {
                    if (*codedMessageBits != *((branchMatrix + (j * rate) + i % rate)))
                    {
                        for (uint8_t n = 0; n < 2; n++)
                        {
                            for (uint16_t p = 0; p < numberOfBranch; p += 4)
                                pathError[n + p + j * 2]++;
                        }
                    }
                }
            }
            else if (i >= rate && i < 2 * rate)
            {
                for (uint16_t m = 0; m < numberOfState; m += numberOfState / 2)
                {
                    for (uint8_t j = 0; j < 2; j++)
                    {
                        if (*codedMessageBits != *(((branchMatrix + m * 2 * rate) + j * rate) + i % rate))
                        {
                            for (uint8_t n = 0; n < 2; n++)
                            {
                                for (uint16_t p = 0; p < numberOfBranch; p += 8)
                                    pathError[n + p + j * 4 + m / (numberOfState / 4)]++;
                            }
                        }
                    }
                }
            }
        }
        else if (i >= (k - 1) * rate && i < k * rate)
        {
            for (uint16_t m = 0; m < numberOfState; m++)
            {
                for (uint8_t j = 0; j < 2; j++)
                {
                    if (*codedMessageBits != *(((branchMatrix + m * 2 * rate) + j * rate) + i % rate))
                    {
                        pathError[2 * m + j]++;
                    }
                }
            }

            if (i % rate == rate - 1)
            {
                for (uint16_t m = 0; m < numberOfState; m++)
                {
                    if (m < numberOfState / 2)
                    {
                        if (pathError[4 * m] < pathError[4 * m + 2])
                        {
                            for (uint16_t j = 0; j < iteration % truncationLength + 2; j++)
                            {
                                pathState[m][j] = *((initialStateMatrix + 2 * m * (k + 1)) + j);
                            }
                            pathStateError[m] = pathError[4 * m];
                        }
                        else
                        {
                            for (uint16_t j = 0; j < iteration % truncationLength + 2; j++)
                            {
                                pathState[m][j] = *((initialStateMatrix + 2 * m * (k + 1)) + j + 1);
                            }
                            pathStateError[m] = pathError[4 * m + 2];
                        }
                    }
                    else
                    {
                        if (pathError[4 * (m - (numberOfState / 2)) + 1] < pathError[4 * (m - (numberOfState / 2)) + 3])
                        {
                            for (uint16_t j = 0; j < iteration % truncationLength + 2; j++)
                            {
                                pathState[m][j] = *((initialStateMatrix + 2 * m * (k + 1)) + j);
                            }
                            pathStateError[m] = pathError[4 * (m - (numberOfState / 2)) + 1];
                        }
                        else
                        {
                            for (uint16_t j = 0; j < iteration % truncationLength + 2; j++)
                            {
                                pathState[m][j] = *((initialStateMatrix + 2 * m * (k + 1)) + j + 1);
                            }
                            pathStateError[m] = pathError[4 * (m - (numberOfState / 2)) + 3];
                        }
                    }
                }

                for (uint16_t n = 0; n < numberOfBranch; n++)
                    pathError[n] = 0;
            }
        }
        else
        {
            for (uint16_t m = 0; m < numberOfState; m++)
            {
                for (uint8_t j = 0; j < 2; j++)
                {
                    if (*codedMessageBits != *(((branchMatrix + m * 2 * rate) + j * rate) + i % rate))
                    {
                        pathError[2 * m + j]++;
                    }
                }
            }

            if (i % rate == rate - 1)
            {
                for (uint16_t m = 0; m < numberOfState; m++)
                {
                    tempPathStateError[m] = pathStateError[m];

                    for (uint16_t n = 0; n <= iteration % truncationLength; n++)
                        tempPathState[m][n] = pathState[m][n];
                }

                for (uint16_t m = 0; m < numberOfState; m++)
                {
                    if (m < numberOfState / 2)
                    {
                        if (tempPathStateError[2 * m] + pathError[4 * m] < tempPathStateError[2 * m + 1] + pathError[4 * m + 2])
                        {
                            if (m == 0)
                            {
                                if (truncationIteration == 1)
                                    pathState[m][(iteration % truncationLength) + 1] = m + 1;
                                else
                                    pathState[m][iteration % truncationLength] = m + 1;

                                pathStateError[m] += pathError[4 * m];
                            }
                            else
                            {
                                for (uint16_t n = 0; n <= iteration % truncationLength; n++)
                                    pathState[m][n] = tempPathState[2 * m][n];

                                if (truncationIteration == 1)
                                    pathState[m][(iteration % truncationLength) + 1] = m + 1;
                                else
                                    pathState[m][iteration % truncationLength] = m + 1;

                                pathStateError[m] = tempPathStateError[2 * m] + pathError[4 * m];
                            }
                        }
                        else
                        {
                            for (uint16_t n = 0; n <= iteration % truncationLength; n++)
                                pathState[m][n] = tempPathState[2 * m + 1][n];

                            if (truncationIteration == 1)
                                pathState[m][(iteration % truncationLength) + 1] = m + 1;
                            else
                                pathState[m][iteration % truncationLength] = m + 1;

                            pathStateError[m] = tempPathStateError[2 * m + 1] + pathError[4 * m + 2];
                        }
                    }
                    else
                    {
                        if (tempPathStateError[2 * (m - (numberOfState / 2))] + pathError[4 * (m - (numberOfState / 2)) + 1] < tempPathStateError[2 * (m - (numberOfState / 2)) + 1] + pathError[4 * (m - (numberOfState / 2)) + 3])
                        {
                            for (uint16_t n = 0; n <= iteration % truncationLength; n++)
                                pathState[m][n] = tempPathState[2 * (m - (numberOfState / 2))][n];

                            if (truncationIteration == 1)
                                pathState[m][(iteration % truncationLength) + 1] = m + 1;
                            else
                                pathState[m][iteration % truncationLength] = m + 1;

                            pathStateError[m] = tempPathStateError[2 * (m - (numberOfState / 2))] + pathError[4 * (m - (numberOfState / 2)) + 1];
                        }
                        else
                        {
                            if (m == numberOfState - 1)
                            {
                                if (truncationIteration == 1)
                                    pathState[m][(iteration % truncationLength) + 1] = m + 1;
                                else
                                    pathState[m][iteration % truncationLength] = m + 1;

                                pathStateError[m] += pathError[4 * (m - (numberOfState / 2)) + 3];
                            }
                            else
                            {
                                for (uint16_t n = 0; n <= iteration % truncationLength; n++)
                                    pathState[m][n] = tempPathState[2 * (m - (numberOfState / 2)) + 1][n];

                                if (truncationIteration == 1)
                                    pathState[m][(iteration % truncationLength) + 1] = m + 1;
                                else
                                    pathState[m][iteration % truncationLength] = m + 1;

                                pathStateError[m] = tempPathStateError[2 * (m - (numberOfState / 2)) + 1] + pathError[4 * (m - (numberOfState / 2)) + 3];
                            }
                        }
                    }
                }

                for (uint16_t n = 0; n < numberOfBranch; n++)
                    pathError[n] = 0;

                if (truncationLength != numberOfMessageBits)
                {
                    if ((iteration + 1) % truncationLength == 0 || (numberOfMessageBits - iteration - 1) == 0)
                    {
                        for (uint16_t m = 0; m < numberOfState; m++)
                        {
                            if (pathStateError[m] < minimumPathError)
                            {
                                minimumPathError = pathStateError[m];
                                selectedPath = m;
                            }
                        }

                        if (numberOfMessageBits - iteration - 1 != 0 || numberOfMessageBits % truncationLength == 0)
                            BacktracePath(&pathState[selectedPath][0], receivedMessageBits, numberOfMessageBits, k, truncationLength, truncationIteration, 0);
                        else
                            BacktracePath(&pathState[selectedPath][0], receivedMessageBits, numberOfMessageBits, k, truncationLength, truncationIteration, 1);

                        truncationIteration++;
                    }
                }
            }
        }

        codedMessageBits++;
    }

    if (truncationLength == numberOfMessageBits)
    {
        for (uint16_t m = 0; m < numberOfState; m++)
        {
            if (pathStateError[m] < minimumPathError)
            {
                minimumPathError = pathStateError[m];
                selectedPath = m;
            }
        }

        BacktracePath(&pathState[selectedPath][0], receivedMessageBits, numberOfMessageBits, k, truncationLength, truncationIteration, 0);
    }
}

void BacktracePath(uint8_t* pathStates, uint8_t* receivedMessageBits, uint8_t numberOfMessageBits, uint8_t k, uint8_t truncationLength, uint16_t truncationIteration, uint8_t lastInfo)
{
    uint8_t currentState;
    uint16_t numberOfStates = (uint16_t)pow(2, k - 1);

    if (lastInfo == 1)
        truncationLength = numberOfMessageBits % truncationLength;

    for (uint8_t i = 0; i < truncationLength; i++)
    {
        if (truncationIteration == 1)
            currentState = pathStates[truncationLength - i];
        else
            currentState = pathStates[truncationLength - i - 1];

        if (lastInfo == 0)
        {
            if (currentState <= numberOfStates / 2)
                receivedMessageBits[truncationLength * truncationIteration - 1 - i] = 0;
            else if (currentState > numberOfStates / 2)
                receivedMessageBits[truncationLength * truncationIteration - 1 - i] = 1;
        }
        else
        {
            if (currentState <= numberOfStates / 2)
                receivedMessageBits[numberOfMessageBits - truncationLength - 1 - i] = 0;
            else if (currentState > numberOfStates / 2)
                receivedMessageBits[numberOfMessageBits - truncationLength - 1 - i] = 1;
        }
    }
}
