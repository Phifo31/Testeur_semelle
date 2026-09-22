


#ifndef CANBUS_H
#define CANBUS_H

void CANBUS_setup (void);
int8_t CANBUS_service (void);

void CANBUS_write_single_coil(uint16_t reg, uint16_t val);
void CANBUS_read_discrete_input(uint16_t reg, uint16_t nb);
void CANBUS_handle_rx_message(void);

#endif //CANBUS_H


