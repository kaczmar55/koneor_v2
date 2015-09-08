#include "eor_cfg.hpp"
#include <QMessageBox>

eorkonf_hdr_t               eorkonf_hdr;
general_cfg_t               general_cfg;
user_cfg_t                  user_cfg[USER_COUNT];
io_module_cfg_t             io_module_cfg[IO_MODULE_COUNT];
jsn2_module_cfg_t           jsn2_module_cfg[JSN2_MODULE_COUNT];
meter_cfg_t                 meter_cfg[METER_COUNT];
general_weather_measure_cfg_t   general_weather_measure_cfg;
weather_autom_cfg_t         weather_autom_cfg[WEATHER_AUTOM_COUNT];
temperatures_cfg_t          temperatures_cfg;
circuit_cfg_t               circuit_cfg[CIRCUIT_COUNT];
group_cfg_t                 group_cfg;
io_cfg_t                    io_cfg;
can_cfg_t                   can_cfg;
modbus_slave_cfg_t          modbus_slave_cfg;
tgfm_cfg_t                  tgfm_cfg;
rs_cfg_t                    rs_cfg[RS_COUNT];
eth_cfg_t                   eth_cfg;

const int32_t eorkonf_data_size = sizeof(general_cfg_t) +
                                sizeof(user_cfg_t) * USER_COUNT +
                                sizeof(io_module_cfg_t) * IO_MODULE_COUNT +
                                sizeof(jsn2_module_cfg_t) * JSN2_MODULE_COUNT +
                                sizeof(meter_cfg_t) * METER_COUNT +
                                sizeof(general_weather_measure_cfg_t) +
                                sizeof(weather_autom_cfg_t) * WEATHER_AUTOM_COUNT +
                                sizeof(temperatures_cfg_t) +
                                sizeof(circuit_cfg_t) * CIRCUIT_COUNT +
                                sizeof(group_cfg_t) +
                                sizeof(io_cfg_t) +
                                sizeof(can_cfg_t) +
                                sizeof(modbus_slave_cfg_t) +
                                sizeof(tgfm_cfg_t) +
                                sizeof(rs_cfg_t) * RS_COUNT +
                                sizeof(eth_cfg_t);

int checkIoMod(uint8_t module_id, uint8_t input_output_type, QString text)
{
    //type: 0 - digital input
    //      1 - digital output
    //      2 - TH
    //      3 - CVM

    if(io_module_cfg[module_id - 1].type == 0)
        return QMessageBox::critical(NULL, "Błąd", text + QString("\nNie ma modułu IO o podanym numerze."), "Ignoruj", "Popraw");

    switch(input_output_type)
    {
    case 0:     //digital input
        if((io_module_cfg[module_id - 1].type != IO10_5_TYPE) &&         /* io10/5 */
                (io_module_cfg[module_id - 1].type != TH_TYPE) &&    /* th     */
                (io_module_cfg[module_id - 1].type != I12_TYPE) &&    /* i12    */
                (io_module_cfg[module_id - 1].type != I20_TYPE) &&    /* i20    */
                (io_module_cfg[module_id - 1].type != IO4_7_TYPE) &&    /* io4/7  */
                (io_module_cfg[module_id - 1].type != GMR_IO_TYPE))      /* gmr io */
        {
            return QMessageBox::critical(NULL, "Błąd", text + QString("\nModuł o podanym numerze nie ma wejść cyfrowych."), "Ignoruj", "Popraw");
        }
        break;
    case 1:     //digital output
        if((io_module_cfg[module_id - 1].type != IO10_5_TYPE) &&         /* io10/5 */
                (io_module_cfg[module_id - 1].type != O10_TYPE) &&    /* o10    */
                (io_module_cfg[module_id - 1].type != IO4_7_TYPE) &&    /* io4/7  */
                (io_module_cfg[module_id - 1].type != GMR_IO_TYPE))      /* gmr io */
        {
            return QMessageBox::critical(NULL, "Błąd", text +  QString("\nModuł o podanym numerze nie ma wyjść cyfrowych."), "Ignoruj", "Popraw");
        }
        break;
    case 2:     //TH
        if(io_module_cfg[module_id - 1].type != TH_TYPE)
        {
            return QMessageBox::critical(NULL, "Błąd", text + QString("\nModuł o podanym numerze nie jest modułem TH."), "Ignoruj", "Popraw");
        }
        break;
    case 3:     //CVM
        if(io_module_cfg[module_id - 1].type != CVM_TYPE)         /* CVM */
        {
            return QMessageBox::critical(NULL, "Błąd", text + QString("\nModuł o podanym numerze nie jest modułem CVM."), "Ignoruj", "Popraw");
        }
        break;
    }

    return 0;
}

bool strToIp(uint8_t *ip, QString string)
{
    QStringList list;
    int i;
    int val;
    bool err = false;
    bool ok;

    list = string.split(".");
    if(list.size() < 4)
    {
        err = true;
    }
    else
    {
        for(i = 0; i < 4; i++)
        {
            val = list[i].toInt(&ok);
            if((ok == false) || (val < 0) || (val > 255))
            {
                err = true;
                break;
            }
            else
            {
                ip[i] = val;
            }
        }
    }
    return err;
}
