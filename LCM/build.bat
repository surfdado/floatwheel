@REM ADV-P42A
cbuild setup Project\MDK5\LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+ADV-P42A --packs
cbuild Project\MDK5\LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+ADV-P42A
copy Project\MDK5\out\LCM_Light_Control_IO_WS2812_New\ADV-P42A\Release\*.hex .

@REM ADV-DG40
cbuild setup Project\MDK5\LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+ADV-DG40 --packs
cbuild Project\MDK5\LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+ADV-DG40
copy Project\MDK5\out\LCM_Light_Control_IO_WS2812_New\ADV-DG40\Release\*.hex .

@REM GTV
cbuild setup Project\MDK5\LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+GTV --packs
cbuild Project\MDK5\LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+GTV
copy Project\MDK5\out\LCM_Light_Control_IO_WS2812_New\GTV\Release\*.hex .

@REM PINTV
cbuild setup Project\MDK5\LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+PINTV --packs
cbuild Project\MDK5\LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+PINTV
cp Project\MDK5\out\LCM_Light_Control_IO_WS2812_New\PINTV\Release\*.hex .

@REM XRV
cbuild setup Project\MDK5\LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+XRV --packs
cbuild Project\MDK5\LCM_Light_Control_IO_WS2812_New.csolution.yml --context-set --context LCM_Light_Control_IO_WS2812_New.Release+XRV
copy Project\MDK5\out\LCM_Light_Control_IO_WS2812_New\XRV\Release\*.hex .
