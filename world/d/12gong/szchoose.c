// by HAPP@YSZZ
#include <ansi.h>

inherit ROOM;

void create ()
{
        set ("short", "������˫����");
        set ("long", @LONG
  ����˹�ʹ������մ���ɫ����˹��Ϊ�ӽ���������Ϊ��죬��������һ��˫��̥-������
˹���Ӻ���֮�ӿ�˹�С����˽�������ð�յ���ʿ�������������´�ѫ�����Ƕ���Ҳ��һ
��˫��̥�õ�-����˹���ֿ�˹��һ������׼��ȥץţ������ץ�˺ܶ�ţ����׼��ƽ��ʱ��
̰�ĵ�����˹���ֿ�˹�ò�����˹����˹���ֵܲ���ʱ����ţȫ������ȥ������ŭ������˫
��̥������ִ���������˹�ü�����˹�д�����������˹���ĵ�Ҫ�濨˹�и��������ȴ��
Ϊӵ����Զ��������������Ը�����ı�ʹ�ж�����˹����Ϊ���Ƕ��������������ֱ�ס����
��������֮����

LONG);
            set("exits", ([
            "left"    :       __DIR__"szchoose",
            "right"  :       __DIR__"szchoose",        
            ]));

  /*      set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/shuangzi" : 1,
        ]));
*/
		set("outdoors", "12gong");
        setup();
        
         
}


int valid_leave(object me,string dir)
{ 
	
        if ( present("shuang zi") && (dir == "right" || dir == "left" ))

        return notify_fail("�յ�����˫�ӹ������һ����Ц��\n");
        
	
    new("/d/12gong/npc/shuangzi")->move(environment(me));
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
