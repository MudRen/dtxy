#include <room.h>
inherit ROOM;
void create()
{
        set("short", "����");
        set("long", @LONG
���õ����룬�������ӣ���������ֻ����ɫ�Ĵ��룬��ʼ���������˵�����
�����������﷢�����ġ������Ȼ��ֻ�յú��ļ�������������ϣ����ǿ�
�����ģ�������һ����Ӱ��
LONG
  );
  set("exits",([
        "west" : __DIR__"didaotou",
        "southeast" : __DIR__"guodao",
        "north" : __DIR__"sleep",
      ]));  
   set("objects", ([
      
      
      __DIR__"zhongshan":1,
     ]) );  
        set("no_magic",1);
        
        create_door("west", "�̻���", "east", DOOR_CLOSED);

        setup();
} 
