/* FIR coefficients calculated using scipy firwin window method */
const float lowpass[] = { /* lowpass @ 200 Hz */
    0.00216882,  0.00224912,  0.00245902,  0.0027991 ,  0.0032684 ,
    0.0038644 ,  0.00458306,  0.00541886,  0.00636478,  0.00741248,
    0.00855227,  0.0097733 ,  0.01106366,  0.01241048,  0.01380011,
    0.01521826,  0.01665019,  0.01808084,  0.01949505,  0.0208777 ,
    0.02221392,  0.02348927,  0.02468987,  0.02580262,  0.02681532,
    0.02771684,  0.02849723,  0.02914788,  0.02966158,  0.03003264,
    0.03025694,  0.03033198,  0.03025694,  0.03003264,  0.02966158,
    0.02914788,  0.02849723,  0.02771684,  0.02681532,  0.02580262,
    0.02468987,  0.02348927,  0.02221392,  0.0208777 ,  0.01949505,
    0.01808084,  0.01665019,  0.01521826,  0.01380011,  0.01241048,
    0.01106366,  0.0097733 ,  0.00855227,  0.00741248,  0.00636478,
    0.00541886,  0.00458306,  0.0038644 ,  0.0032684 ,  0.0027991 ,
    0.00245902,  0.00224912,  0.00216882
};

/*
// 1k 1 gain + 1.5k 0.5 gain
const float test_lowpass[29] = {-0.0018225230, -0.0015879294, +0.0000000000, +0.0036977508, +0.0080754303, +0.0085302217, -0.0000000000, -0.0173976984, -0.0341458607, -0.0333591565, +0.0000000000, +0.0676308395, +0.1522061835, +0.2229246956, +0.2504960933, +0.2229246956, +0.1522061835, +0.0676308395, +0.0000000000, -0.0333591565, -0.0341458607, -0.0173976984, -0.0000000000, +0.0085302217, +0.0080754303, +0.0036977508, +0.0000000000, -0.0015879294, -0.0018225230};
*/
const float test_lowpass[29] = {-0.0010009622, -0.0006384356, +0.0000000000, +0.0014867007, +0.0044351707, +0.0093699005, +0.0165975413, +0.0261050924, +0.0375070343, +0.0500551189, +0.0627132970, +0.0742881322, +0.0835943570, +0.0896280755, +0.0917179550, +0.0896280755, +0.0835943570, +0.0742881322, +0.0627132970, +0.0500551189, +0.0375070343, +0.0261050924, +0.0165975413, +0.0093699005, +0.0044351707, +0.0014867007, +0.0000000000, -0.0006384356, -0.0010009622};
const float bandpass[] = { /* bandpass 500 - 1000 Hz */
    -4.01660803e-03,  -4.12318049e-03,  -4.41700812e-03,
    -4.87387120e-03,  -5.45367850e-03,  -6.10190830e-03,
    -6.75181063e-03,  -7.32728593e-03,  -7.74632268e-03,
    -7.92484765e-03,  -7.78082122e-03,  -7.23839507e-03,
    -6.23194329e-03,  -4.70978017e-03,  -2.63738833e-03,
    5.18604292e-18,   3.19559977e-03,   6.92014645e-03,
    1.11219070e-02,   1.57276488e-02,   2.06445451e-02,
    2.57629533e-02,   3.09599640e-02,   3.61035830e-02,
    4.10573788e-02,   4.56854084e-02,   4.98572160e-02,
    5.34526992e-02,   5.63666362e-02,   5.85126862e-02,
    5.98266911e-02,   6.02691401e-02,   5.98266911e-02,
    5.85126862e-02,   5.63666362e-02,   5.34526992e-02,
    4.98572160e-02,   4.56854084e-02,   4.10573788e-02,
    3.61035830e-02,   3.09599640e-02,   2.57629533e-02,
    2.06445451e-02,   1.57276488e-02,   1.11219070e-02,
    6.92014645e-03,   3.19559977e-03,   5.18604292e-18,
    -2.63738833e-03,  -4.70978017e-03,  -6.23194329e-03,
    -7.23839507e-03,  -7.78082122e-03,  -7.92484765e-03,
    -7.74632268e-03,  -7.32728593e-03,  -6.75181063e-03,
    -6.10190830e-03,  -5.45367850e-03,  -4.87387120e-03,
    -4.41700812e-03,  -4.12318049e-03,  -4.01660803e-03
};

const float highpass[] = {
    6.52135292e-04,   6.18334428e-04,   5.97872017e-04,
    5.75027285e-04,   5.29468848e-04,   4.36934775e-04,
    2.70157463e-04,  -7.75979765e-18,  -4.03240285e-04,
    -9.68414606e-04,  -1.72205235e-03,  -2.68690246e-03,
    -3.88055291e-03,  -5.31419328e-03,  -6.99158078e-03,
    -8.90826297e-03,  -1.10511005e-02,  -1.33981213e-02,
    -1.59187238e-02,  -1.85742327e-02,  -2.13187949e-02,
    -2.41005892e-02,  -2.68633089e-02,  -2.95478649e-02,
    -3.20942455e-02,  -3.44434628e-02,  -3.65395103e-02,
    -3.83312543e-02,  -3.97741851e-02,  -4.08319575e-02,
    -4.14776584e-02,   9.58979279e-01,  -4.14776584e-02,
    -4.08319575e-02,  -3.97741851e-02,  -3.83312543e-02,
    -3.65395103e-02,  -3.44434628e-02,  -3.20942455e-02,
    -2.95478649e-02,  -2.68633089e-02,  -2.41005892e-02,
    -2.13187949e-02,  -1.85742327e-02,  -1.59187238e-02,
    -1.33981213e-02,  -1.10511005e-02,  -8.90826297e-03,
    -6.99158078e-03,  -5.31419328e-03,  -3.88055291e-03,
    -2.68690246e-03,  -1.72205235e-03,  -9.68414606e-04,
    -4.03240285e-04,  -7.75979765e-18,   2.70157463e-04,
    4.36934775e-04,   5.29468848e-04,   5.75027285e-04,
    5.97872017e-04,   6.18334428e-04,   6.52135292e-04
};
