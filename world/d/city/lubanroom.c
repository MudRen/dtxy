inherit ROOM;
#include <ansi.h>
void create()
{
 set("short","�෿");
        set("long", @LONG

��䲻�����յ�������³���ס��, ��˽а෿. ��֪Ϊ��,
������������Ϊ�η�֮��. ��Ȼ�����������, ȴҲʮ������
������¯���ڲ�ͣ��Ϊ�������Ʊ���. ǽ���ϻ�����һ������
(paizi), ����д��ʲô.

LONG
        );
        set("exits", ([
                "up" : __DIR__"droproom",
        ]));
        set("objects",
        ([ //sizeof() == 1
               __DIR__"npc/luban" : 1,
        ]));
        set("no_fight", 1);
        set("no_magic", 1);
        set("item_desc", ([
                "paizi": @TEXT
����ʹ�õ�ָ����:

register         ע��װ����
deregister       ע��װ����
fetch            ȡ��ע���װ��
list             �鿴ע���װ��
payoff           ���屣�ܷ�
luimprove        ��³���������װ��
selfimprove      �Լ���������װ��
luembed          ��³�������Ƕ��ʯ
selfembed        �Լ�������Ƕ��ʯ
upgrade          ��װ��������һ�ȼ�

TEXT
        ]) );
        setup();
}