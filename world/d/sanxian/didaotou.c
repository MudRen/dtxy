// edited by mind
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "�ص���ͷ");
        set("long", @LONG
�ص�����������ͷ����һ���ţ�������Ҳ�����һЩ���ﻨ�ݣ���������ֻ
�������ص����Ͳ�֪���˶���������������������˿ϻ���ô������������ڵ�
�½������ߵ������治֪�Ǹ�ʲô���Ĺ��
�ţ���û��������
LONG
  );
  set("exits",([
        "west" : __DIR__"didao1",
        "east" : __DIR__"huating",
      ]));  
   set("objects", ([
      
     ]) );  
        set("no_magic",1);
        
        create_door("east", "�̻���", "west", DOOR_CLOSED);
        setup();
} 
