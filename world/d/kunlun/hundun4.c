inherit ROOM;                                                        
                                                                     
void create ()                                                       
{                                                                    
  set ("short", "������");                                   
  set ("long", @LONG                                                 
 
����һƬ����ʹ���Ҫ�ֲ��巽�򣬻��ǳ��ܿ���

·��ʱ��Ͽ��߰ɡ�
                                           
LONG);                                                          
                                                                     
    set("exits", ([ /* sizeof() == 1 */                              
  "north" : __DIR__"hundun1",                                         
  "east" : __DIR__"hundun5",                                    
  "west" : __DIR__"hundun2",                                       
  "south" : __DIR__"hundun3",
                                     
]));                                                                 
                                                                     
  setup();                                                           
}
