@REM ADV2
cbuild setup Project\MDK5\BMS_VESC_Code_N32L4.csolution.yml --context-set --context BMS_VESC_Code_N32L4.Release+ADV2 --packs
cbuild Project\MDK5\BMS_VESC_Code_N32L4.csolution.yml --context-set --context BMS_VESC_Code_N32L4.Release+ADV2
copy Project\MDK5\out\BMS_VESC_Code_N32L4\ADV2\Release\*.hex .
