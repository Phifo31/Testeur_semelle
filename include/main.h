

#ifndef MAIN_H
#define MAIN_H

// ─── Pins & IDs ───────────────────────────────────────────────

#define MASQUE_CAPTEUR_BUTEE_HAUTE 0x01
#define MASQUE_CAPTEUR_BUTEE_BASSE 0x02

#define VERRIN_PRINCIPAL_POUSSE 0
#define VERRIN_PRINCIPAL_TIRE 1
#define VERRIN_AMORTISSEUR 2


#define CAN_TX_PIN 6
#define CAN_RX_PIN 0
#define GPIO_CAN_ID 0x42   // ID de la carte GPIO
#define MASTER_CAN_ID 0x99 // ID de la carte écran

#define FOREVER 1
#define PERIODE_CYCLE 50

#define USB_ACTIVITY_PERIOD 1000
#define APPLICATION_PERIOD 50

typedef union WORD_BYTE
{
    uint16_t w;
    uint16_t uval;
    int16_t sval;

    struct
    {
        uint8_t lo;
        uint8_t hi;
    } b;
} word_byte_t;

// interface entre canbus et application
void process_input(uint8_t val);

extern HWCDC USBSerial;

#endif // MAIN_H
