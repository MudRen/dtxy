// by HAPP@YSZZ
#include <ansi.h>

inherit ROOM;
int block_cmd(string);
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
            "southup"    :       __DIR__"sz2jx1",
            "westdown"  :       __DIR__"jn2sz2",        
            ]));

        set("outdoors", "12gong");
        setup();
        
         
}

int valid_leave(object me, string dir)
{
       if (me->query_temp("12gong/cike") == "done")
	{
		   message_vision("\n\nһ��ʱ�յ���Ť,�㱻һ�����ص������ͳ���˫�ӹ�!\n",me);  
	       message_vision("\n�ٺ�...�ٺ�,��մ���һ����ɭ��Ц��:�ŵ�������������!\n",me);  
		   message_vision("\n�㲻�ɵ�����һ�󲻰�!\n\n\n",me);   
		  if((me&&me->query("12gong/jinniu")=="done") && (me&&me->query("12gong/shuangzi")!="done"))
        {
        me->start_busy(3);
        message("chat",HIY+"���ƽ�ʮ����������(saga):"+me->name()+
        "�����˵�������˫�����Թ�������������\n"NOR,users());
        me->set("12gong/shuangzi","done");
        me->add("12gong/number",1);
          me->add("combat_exp", 10000);
tell_object(me,"��õ���ʮ�����\n");

        }
		  return 1;
	}
		
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
