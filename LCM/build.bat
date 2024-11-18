@REM ADV
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+ADV --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+ADV
copy Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/ADV/Release/*.hex .

@REM GTV
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+GTV --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+GTV
copy Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/GTV/Release/*.hex .

@REM PINTV
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+PINTV --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+PINTV
cp Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/PINTV/Release/*.hex .

@REM XRV
cbuild setup Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+XRV --packs
cbuild Project/MDK5/LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+XRV
copy Project/MDK5/out/LCM_Light_Control_IO_WS2812_New/XRV/Release/*.hex .
