#include <ansi.h>
inherit ROOM;
void create()
{
    set("short", "�ķ�");
    set("long", @LONG
����ķ�����ů�紺��ɢ��һЩ��ʱ�С���־��һ�����׻����Է����������
ζ������ϸ���������м���ͷ����ʪʪ����ģ���������������ķ���д�˼���
��(words)�����������ġ�
LONG);
        set("sleep_room", 1);
        set("no_death", 1);
        set("valid_startroom", 1);
        set("exits", ([
            "down" :"/d/city/kezhan.c",
            "up" :"/d/wiz/wizroom.c",
            "city" :"/d/city/center.c",
            "longgong" :"/d/sea/gate.c",
        ]));
        set("item_desc", 
        (["words" : 
             HIC" ����ī����С�ӣ��Ҹ���û�ꡣ\n"NOR, 
        ]));

        replace_program(ROOM);
}
