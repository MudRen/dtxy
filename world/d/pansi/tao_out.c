//�һ�����
//lestat 2001
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short", HIM"�һ�����"NOR);
        set("long",
"����һƬ"+HIM"�һ�"NOR+"�ĺ�������һ���޼ʣ�ȫ��ʢ����"+HIM"�һ�"NOR+"��΢�������
��Ӣ�ͷס���Χ�����ĵġ�Զ��ż������һ����С�������һƬ��
���֣�����Զ��ңң�������¡¡��ˮ��,�ƺ��и�"+HIC"�ٲ�"NOR+"��\n"
 );
       set("exits", ([
           "south" : __DIR__"tao0",
           "north" : __DIR__"pubu",
       ]));
       set("outdoors","taohua");
       set("no_clean_up", 0);
       setup();
}
