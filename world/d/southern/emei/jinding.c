//Cracked by Roath
// ajax

inherit ROOM;

void create()
{
set("short", "��");
set("long", @LONG
    
    ���ҽ����Ĵ���ۣ��ƺ����ճ������ͷ�ơ��������Է��
��Ϊ����������ƽ�羲�����ᣬ�ܻ�������Ʋ��һ��������������
������Լ��ʹ⻷���ۿ��⻷ʱ���ɼ����а�Ӱ�����Ӱ��һ������
ÿ����ֻ�ܿ����Լ�����Ӱ�����ܿ���������Ӱ��������ʫӽ�ޣ���
���Ʒ������գ��������Ĳ�ͬ��������ʯ�ߴ��������˶��ڷ��
�С���

LONG );


set("exits", ([
  "west"   : __DIR__"sheshenyan",
  "eastdown"   : __DIR__"daochang",
 
]));


set("objects", ([
"/d/southern/emei/npc/dashizhi": 1,
]));



set("outdoors", 1);

setup();
}
