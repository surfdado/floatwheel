# ADV-P42A
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+ADV-P42A --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+ADV-P42A
cp Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/ADV-P42A/Release/*.hex ./

# ADV-DG40
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+ADV-DG40 --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+ADV-DG40
cp Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/ADV-DG40/Release/*.hex ./

# GTV
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+GTV --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+GTV
cp Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/GTV/Release/*.hex ./

# PINTV
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+PintV --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+PintV
cp Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/PintV/Release/*.hex ./

# XRV
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+XRV --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+XRV
cp Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/XRV/Release/*.hex ./
