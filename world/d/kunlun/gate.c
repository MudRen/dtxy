#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���鶴���");
        set("long", 
"�˴������鶴��ڣ������ɾ��쳣�����˰��治Ͼ����ʫΪ֤��
�ɷ����ۣ�������ͣ�������ݣ��س���֥���������㣬����
���룻�����������Ͼպ�÷���������ӣ����潻�棻�����л���
����Χ�塣\n"+

"�ſ�һ���޴�ʯ����д�ţ�\n"+
HIW"    ��    ��    ɽ    ��    ��    ��  \n"NOR
);
        set("exits", ([ /* sizeof() == 2 */
  "northup" : __DIR__"shijie1",
  "southdown" : __DIR__"xiaolu3",


]));
    set("objects", ([ // sizeof() == 1 //
  __DIR__"npc/xiaotong" : 2,
]));
        setup();
  call_other("/obj/board/yubi_b", "???");
        replace_program(ROOM);
}
