//Cracked by Roath
//  ����֮�� ������
//  by happ@YSZZ 2000.4.7
//  /d/qujing/huangfeng/road1.c

inherit ROOM;

void create ()
{
  set ("short", "ɽ·");
  set ("long", @LONG

ɽ·���Ա���һ��ʯ�£�ʯ�����ʳ�һ����ʯ�����飺
[33m
                �áááááááá�
                �� [1;37m�Ʒ���Ʒ綴 [0;33m��
                �áááááááá�[m

LONG);
  set("exits", ([
        "westdown"  : "/d/qujing/liusha/dadao1",
        "eastdown"  : __DIR__"shanlu4",
        "northdown": __DIR__"in1",
        "south":   __DIR__"zhaozhe",
          ]));
  set("outdoors","hfd");
  setup();
}
