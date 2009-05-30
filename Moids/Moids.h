#pragma once

/** Moid Class Definition
 */	       
class Moids
{
public:
    // ctor
    Moids();

    // ������
    void init();
    void setInputMicPin(const int pin);
    void setOutputLEDPin(const int pin);
    void setOutputRelayPin(const int pin);

    // 臒l�̐ݒ�
    void setMicThreshold(const int thres);

    // on���Ԃ̐ݒ�
    void setRelayOnTime(const int time);

    // ��������܂ł̎���
    void setWaitAfterSoundDetect(const int time);
    // �^�C�}�[�̃R�[���o�b�N
    void tick();

    // loop ����}�C�N�̉��ʂ�ǂ݂ɍs��
    void loop();

    // ���̒���o�^����
    void registerOtherMoids(Moids* moids);

    // ���̒��Ɏ������������ĉ����o���Ă��邱�Ƃ�m�点��
    void broadCastGenerateSoundState(bool start);

    // ���̒�����̃��b�Z�[�W����M����
    void receiveOtherMoidsMessageSoundState(bool start, int relayPin);
    
private:
    int m_micOffset;
    int m_micThreshold;
    unsigned long m_relayOnTime;
    unsigned long m_relayOnTimeCounter;
    
    unsigned long m_waitAfterDetect;
    unsigned long m_waitAfterDetectCounter;

    unsigned long m_nopWait;
    unsigned long m_nopWaitCounter;
    
    // enum for interactive functions
    enum MoidsState
    {
	ReadAnalog = 0,
	SoundInput,
	GenerateSound,
	Nop,
	NumberOfStates,
    };
    int m_state;
    
    // state functions
    void changeState(const int state);
    void tickReadAnalogState();
    void tickSoundInputState();
    void tickGenerateSoundState();
    void tickNopState();
    // function pointer for state
    void (Moids::*m_stateFunction)();
    
    volatile unsigned long m_timerCounter;

    // pins
    volatile int m_inputMicPin;
    volatile int m_outputLEDPin;
    volatile int m_outputRelayPin;
    
    // mic input workaround
    void readAnalogInput();
    bool checkInput();
    static const int MIC_INPUT_ARRAY_LENGTH = 2;
    volatile int m_micInput[2];
    bool m_firstTimeAfterStateTransition;
    volatile int m_dontReadCounter;
    void makeOffset();
    volatile bool m_detect1stTime;
    
    static const unsigned long COUNTER_PER_1MSEC = 8;
    static const int LED_BRIGHTNESS_WAITING = 1;
    static const int LED_BRIGHTNESS_INPUT_DETECTED = 2;
    static const int LED_BRIGHTNESS_SOUND_GENERATING = 4;

    static const int NUM_OTHER_MOIDS = 2;
    volatile int m_numOtherMoids;
    Moids* m_otherMoids[NUM_OTHER_MOIDS]; // ���̒�
};

