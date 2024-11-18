# ADV
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+ADV --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+ADV
cp Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/ADV/Release/*.hex ./

# GTV
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+GTV --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+GTV
cp Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/GTV/Release/*.hex ./

# PINTV
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+PINTV --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+PINTV
cp Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/PINTV/Release/*.hex ./

# XRV
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+XRV --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+XRV
cp Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/XRV/Release/*.hex ./
