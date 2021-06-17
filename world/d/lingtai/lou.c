//by take
#include <ansi.h>

inherit ROOM;
int do_qiansi();


void create()
{
  set ("short", "С��");
  set ("long", @LONG

�����Ǿ����е�һ��С�ң�Ϊ�������ж������ṩ��һ��������
�ط���ǽ�Ϲ���һ��������д�ţ�Ǳ˼�붨���ĸ����ɷ���Ĵ�
�֣���˵������λ���Լ��ߵ�ǰ��ÿ���ڴ�Ǳ˼, һ��ͻȻ����
�������������ڿ��з�������, �����������ǧ������������.

LONG);
set("exits", ([ /* sizeof() == 4 */
"down": __DIR__"jingge",
]));
        set("no_clean_up", 0);
        setup();
   //     replace_program(ROOM);
}

void init()
{
        add_action("do_qiansi", "qiansi");
}

int do_qiansi()
{
	object me;
    me=this_player();
if (((string)me->query("family/family_name")!="����ɽ���Ƕ�")&&(!wizardp(me)))
    return notify_fail("������̨����,Ǳ˼�붨Ҳû���ô���\n");

	if (me->is_busy() || me->query_temp("pending/exercising")|| me->query_temp("pending/meditating")||me->is_fighting())
    return notify_fail("����æ����,��ʲô��\n");

  	if (me->query("fangcun/panlong_qiansi_finish")==1)
	{
         message_vision(HIW"$N�������£�����Ǳ˼������С���๦,ֻ���ú�ȥ�������ֽ����ۻص���.\n"NOR,me);
         if (me->query("force")>=me->query("max_force")*2)
              return 1;
		 me->add("force",(random(me->query_skill("wuxiangforce")))*4+100);
         me->start_busy(10);
		 return 1;
	}
	
	if (!me->query("fangcun/panlong_qiansi"))
	{
		set("start",1);
		me->set("fangcun/panlong_qiansi",1);
	}

	if (query("start")==1)
    {

		me->add("fangcun/panlong_qiansi",1);
		set("start",0);
		call_out("add_qiansi",3600);
	}
	
	me->start_busy(random(me->query("int")));

   message_vision(HIW"$N�������£�����Ǳ˼��\n"NOR,me);
     
           if ((me->query("fangcun/panlong_qiansi")>=(me->query_skill("qianjun-bang"))/8)&&(me->query("family/generation")<3))
	{
		me->set("fangcun/panlong_qiansi_finish",1);
		if( random(me->query("int")) > 20 - random( me->query("lunhui_zhuanshi") ) )
		{
			call_out("finish_qiansi",5);
			return 1;
		}

       
	call_out("finish_qiansi2",5);
    
	}  
    
   return 1;
}


void add_qiansi()
{
	remove_call_out("add_qiansi");
	set("start",1);
    return;
}

void finish_qiansi()
{
	object me;
    me=this_player();
	me->start_busy(60);
	me->set_temp("fangcun/qiansi_gongxi",1);
	message_vision(HIY"\n\n\n����ʱ�پ�������������,��ǰ����ʢ.$N���ɵ��������۾�.\n\n"NOR,me);
	message_vision(HIY"\nֻ����������������,���а����������������������.\n\n"NOR,me);
	message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ǧ����(Qianli yan)������ɽ���Ƕ�ǰ�й������������,Ī��������ֻ���ӣ�����������\n\n\n"NOR,users());
  	call_out("finish_qiansi6",3);
    
}

void finish_qiansi2()
{
	object me;
    me=this_player();
	me->set("fangcun/panlong_noway",1);
	message("chat",HIC+"\n\n��"+HIY+"����ҥ��"+HIC+"��������ʦ��������һ��̾�˿�����\n\n\n"NOR,users());
    message("chat",HIC+"��"+HIW+"����ҥ��"+HIC+"��������ʦ(Master puti)����ͽ��"+me->query("name")+"Ե��δ�����ղ��ܽ�ǧ������֮���ϣ���ϧ��������ϧ��\n\n"NOR,users());
    call_out("finish_qiansi3",3);
}

void finish_qiansi3()
{
	object me;
    me=this_player();
	message_vision("\n\n������ʦ(Master puti)���µ����ΪʦҲֻ������㶫��,���������Ǳ˼֮Ը��\n\n"NOR,me);
  	message_vision(HIY"\n������������һ��,$Nֻ���ñ�������,��ǧ����������ʶ�ֽ���һ��.\n\n"NOR,me);
    me->add("str",2);
    call_out("finish_qiansi4",2);
}

void finish_qiansi4()
{
	object me;
    me=this_player();
	message_vision(HIW"\n������ʦҡ��ҡͷ,��ƮȻ��ȥ��.\n\n"NOR,me);
}

void finish_qiansi6()
{
   object me,wan,dao1;
   me=this_player();
   wan=new("/d/lingtai/npc/wanfeng");
   dao1=new("/d/lingtai/npc/xiao");
  dao1->move(environment(me));
  message_vision("\n\n����һ��С��ʿ�����������˽���!\n"NOR,me);
   wan->move(environment(me));
   call_out("finish_qiansi7",3);
}

void finish_qiansi7()
{
   object me,guang1,dao;
   me=this_player();
   guang1=new("/d/lingtai/npc/guangxi");
   dao=new("/d/lingtai/npc/xiaodao");
  dao->move(environment(me)); 
message_vision("\n�����ӿ첽���˽�����\n\n"NOR,me);
   guang1->move(environment(me));
   call_out("finish_qiansi8",5);
message_vision("\n���Ź����ӵĺ��滹������ɨ�ص�Сͯ��\n"NOR,me);
}

void finish_qiansi8()
{
   object me,bo;
   me=this_player();
   bo=new("/d/lingtai/npc/shixong");
   message_vision("\nǽ��һ����Ӱ����,ԭ����𫲻�������л�λ������������\n"NOR,me);
    bo->move(environment(me));
   call_out("finish_qiansi9",3);
}
void finish_qiansi9()
{
   object me,hui1,hui2;
   me=this_player();
   hui1=new("/d/lingtai/npc/huigang");
   hui2=new("/d/lingtai/npc/huiliu");
   message_vision("\n��һ��,����,�۸� ��λ����Ҳ����С�ң�\n"NOR,me);
    hui1->move(environment(me));
	hui2->move(environment(me));
   call_out("finish_qiansi10",3);
}

void finish_qiansi10()
{
   object me,yun1,yun2,yun3;
   me=this_player();
   yun1=new("/d/lingtai/npc/yunjing");
   yun2=new("/d/lingtai/npc/yunqing");
   yun3=new("/d/lingtai/npc/yunxiao");
   message_vision("\n����,�ƾ�Ҳ��̸�����\n"NOR,me);
   yun1->move(environment(me));
   yun2->move(environment(me));
   message_vision("\nԶԶ�ľʹ�����������̾��.\n"NOR,me);
   yun3->move(environment(me));
  call_out("finish_qiansi11",3);
}

void finish_qiansi11()
{
   object me,guang2,chen,zhangdaoling;
   me=this_player();
   guang2=new("/d/lingtai/npc/guangyun");
   
    chen=new("/d/lingtai/npc/yingke");
	zhangdaoling=new("/d/lingtai/npc/zhangdaoling");
   message_vision("\n�����Ӵ���ƮƮ,�㲻��صĻ���������\n"NOR,me);
      guang2->move(environment(me));
   message_vision("\nͻȻ���⴫����ʦ �ŵ����Ц��.\n"NOR,me);
      zhangdaoling->move(environment(me));
   message_vision("\nС�ҵ��ſ�¶��ӭ��Сͯ���µ�С�Դ�,��͵͵���������.\n"NOR,me);
call_out("finish_qiansi12",3);
}

void finish_qiansi12()
{
	object me,yunyang;
    me=this_player();
   yunyang=new("/d/lingtai/npc/yunyang");
   message_vision(WHT"\n�����ﴫ��������������������:����,����ȥɽ��ӭ��ȥ��\n"NOR,me);
   message_vision("\n������������ͷһ������ͷ������.\n\n\n"NOR,me);
  yunyang->move(environment(me));
  call_out("finish_qiansi13",5);
}

void finish_qiansi13()
{
  object me;
  me=this_player();
   	message("chat",HIC+"\n\n��"+HIY+"����ҥ��"+HIC+"��������ʦ��"+me->query("name")+"������Ц�˼�����\n\n"NOR,users());

	message("chat",HIC+"��"+HIW+"����ҥ��"+HIC+"��������ʦ(Master puti)����ͽ��"+me->query("name")+"��������ʽ��Ҫ����������������ܲ������ջ�Ҫ�����
�컯��"+me->query("name")+",��,��,��,����Щ��Ҫ����˵��\n\n\n"NOR,users());
     message_vision(HIW"\n����������ң������.\n\n\n"NOR,me);
     me->delete_temp("fangcun/qiansi_gongxi");
	 me->start_busy(1);
}




