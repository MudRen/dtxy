// by HAPP@YSZZ
#include <ansi.h>

inherit ROOM;
int block_cmd(string);
void create ()
{
        set ("short", "�ڶ�����ţ��");
        set ("long", @LONG
    ��ϣ����Ī���ǵط��ı���˹�ӣ���������˹��λ�����Ĺ�����������һ�죬
��������Ů�ǵ�Ұ��ժ������ˣ��ͻȻ����һֻ��ѩ�����׵�ţ���Լ�������۹�����
��������ʵ��ֻţ����Ľ������ɫ����˹��ġ�һ��ʼ������ȷ���һ��������������
ѱ��ţֻ���ԣ����ḧ���������ڹ�ţ�Ե÷ǳ����ɶ���ѱ�����ǹ����ͷ��ĵ�����ţ��
�������Ȼ��ţ����������������������ٺ�������������ţ����������Գ�������˹
���񣬹�������֪��ţ����˹�Ļ������˿����ص��󣬾ͺ���˹���л��񣬻���Ϊţ��
��˹�ͺ������������Ҹ������ӡ�

LONG);


        set("exits", ([
        "westup"    :       __DIR__"jn2sz1",
        "northdown"  :       __DIR__"by2jn2",        
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/jinniu" : 1,
        ]));
        set("outdoors", "12gong");
        setup();
}

int valid_leave(object me, string dir)
{
        if ( present("aldebaran") && dir == "westup" )
        return notify_fail("��³�ϰ���Ц��:�ȹ��������˵��\n");
        return ::valid_leave(me, dir);
}

void init()
{
    add_action("block_cmd", "", 1);
}
int block_cmd(string args)
{
string verb;
verb = query_verb();
    if (verb == "recall") return 1;
    return 0;
}
