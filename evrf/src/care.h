#ifndef CARE_H
#define CARE_H

// Endovenous - Transcutaneous - Proctology
const int PROTOCOLES[][3][9] = {
    {
    // cr45i
    { 0, 25, 20, 25, 0, 0, 0, 0, 0 },
    // cr40i
    { 1, 25, 20, 25, 0, 0, 0, 0, 0 },
    // cr30i
    { 2, 16,  8, 25, 0, 0, 0, 0, 0 }
},
{
    // Transcutaneous
    { 3, 0, 0, 0, 0, 0, 0, 0, 0 }
},
{
     // hpr45i
     { 4, 25, 20, 25, 0, 0, 0, 0, 0 },
     { 5, 25, 20, 25, 0, 0, 0, 0, 0 }
}
};

class Care
{
public:
    Care();
    int no, power, powermin, powermax, pulsewidth, delay, veindiameter, manualpreset, faceleg;
};

#endif // CARE_H
