// longear.c
// 1996/12/06 by cglaem
#include <ansi.h>

inherit NPC;

string send_mail();
string receive_mail();
string choose;
int begin_go();
object copy_yao(object ob);

void create()
{
	set_name("˳���", ({"shunfeng er", "er", "longear",
"youchai","chai" }) );
	set("title", "�ʲ�");
	set("gender", "����" );
	set("age", 30);
	set("long",
		"ǰ��ʴ�����š���Ϊ͵����ʴ�۸��϶���������Ϊ�ʲ\n");
	set("combat_exp", 8000);
  set("daoxing", 100000);

	set("attitude", "friendly");
	set("inquiry", ([
                        "name":"�����㶼����ʶ������������˳��������ҡ�", 
		"here" : "��֪������ʲô�ط�����ֻ�������ŷ��š�",
                        "�϶�" : "��...��ϧֻ������δ�����ˡ�",
                        "��ʴ��" : "���������һ���Ҿ�����...ֻ���ݹٷŻ𣬲�����յ�ơ�",
		"��ѧ�鼮"    : (: begin_go :),
	    "book"   : (: begin_go :),
	    "����" : (: send_mail :),
		"����" : (: receive_mail :),
		"�ż�" : (: receive_mail :),
		"��" : (: receive_mail :),
		"mail" : "��������������ɣ���������Ү~~~~~~~~",
	]) );
	set_skill("literate", 70);
	set_skill("dodge", 50);
	set_skill("unarmed", 40);
	set("per", 15);
            set("max_kee", 500);
            set("max_gin", 100);
            set("max_sen", 300);
            set("force", 150);
            set("max_force", 300);
            set("force_factor", 0);
	setup();
	add_money("coin", 70);
	carry_object("/d/ourhome/obj/linen")->wear();
}

string send_mail()
{
	object mbox;

	if( this_player()->query_temp("mbox_ob") )
		return "������仹�ڰɣ�������Ϳ��Լ����ˡ�\n";
	if( !environment()
	||	base_name(environment()) != query("startroom") )
		return "��һ�µ���ʯͷ�����Ұɡ�\n";
	seteuid(getuid());
	mbox = new(MAILBOX_OB);
	mbox->move(this_player());
	return "Ŷ... Ҫ������������������䣬���ŵķ�����������˵����\n";
}

string receive_mail()
{
	object mbox;

	if( this_player()->query_temp("mbox_ob") )
		return "������仹�ڰɣ������е��Ŷ������档\n";
	if( !environment()
	||	base_name(environment()) != query("startroom") )
		return "��һ�µ���ʯͷ�����Ұɡ�\n";
	seteuid(getuid());
	mbox = new(MAILBOX_OB);
	mbox->move(this_player());
	return "�ã���������....���ˣ�����������⣬�������ɣ���������ˡ�\n";
}

int begin_go()
{
	object me,ob;
    me=this_player();
	ob=this_object();
    
		if (random(2)==1) choose="��";
		  else
	    choose="��";		
		if (me->query("fangcun/panlong_putuo")!="begin")
	       return 0;
       if (me->query_temp("longear_cured"))
	     {
		   call_out("answer_book",1);
		   return 1;
		 }
      if (me->query_temp("putuo/longear"))
	     {
		  message_vision ("\n˳����૵�����,�������ˣ�\n",me);
		  return 1;
		 }
	  
	   me->set_temp("putuo/longear",choose);
     command("say �߿��߿�,�⼸����"+choose+"�����ַ���ë����,�۵�����,˭���������ң�\n");
     return 1;

}

void answer_book()
{
	object me;
    me=this_player();
    message_vision ("˳�����Ŷ����һ������ԭ��"+RANK_D->query_respect(me)+"Ҫ����������ٺ٣�������˳�Ͷ�����\n\n",me);
    command("say "+RANK_D->query_respect(me)+"��Ҫ����ϸ�ˣ�\n");
    message_vision (HIW"˳���������һ��������\n\n",me);
    message_vision ("ֻ������л���Ʈ����һ�����ᣮ\n"NOR,me);

	call_out("answer_book1",2);
}

void answer_book1()
{
	object me,ob,wuxuebook;
    me=this_player();
    ob=this_object();
	message_vision ("�����ᾹȻƮ����$N�Ļ��\n\n",me);
    command("say "+RANK_D->query_respect(me)+"���������һ��˶���ʱ��鵽������ѧ�鼮����ļ�¼������������ˣ�\n");
    wuxuebook=new("/d/nanhai/obj/wuxuebook");
	wuxuebook->move(me);
	ob->delete_temp("cured");
	me->delete_temp("longear_cured");
   me->delete_temp("putuo/longear");
}

int accept_object (object who, object ob)
{
  object me = this_object();
  object ob2;
  string msg = "$N˵������λ"+RANK_D->query_respect(who);
  string msg1 = "$N˵��������"+RANK_D->query_rude(who);

  if (!who->query_temp("putuo/longear"))
	  return 0;
  
  if (me->query_temp("cured"))
  {
    if (ob->query("id") != "yao")
	  {
      	message_vision (msg+"���Ǻ��⣿\n",me);
		return 1;
	  }

	message_vision (msg+"̫�����ˣ��Ҷ����Ѿ�����,�������鷳�ˣ�\n",me);
    call_out("destroy_object",1,ob);
    return 1;
  }  
  
  if (ob->query("id") != "yao")
  {
    message_vision (msg1+"�����������۵�����,��������Щ���߰���Ķ�����\n",me);
    return 1;
  }

    
  message_vision ("˳�������ҩ�����Ű��ɵĿ��˿���\n",me);
  call_out("delayed_vision",1,
           "Ȼ��һ��������ȥ��\n",me); 
  ob2 = copy_yao(ob);
  call_out("eat_drug",3,me,ob2,who);
  return 1;
}

void delayed_vision (string msg, object me)
{
  message_vision (msg,me);  

}

void destroy_object (object ob)
{
  destruct (ob);
}

void eat_drug (object me, object ob, object who)
{
      if (! ob->query_temp("is_longear"))
  {
    message_vision ("$NͻȻһ���Ӷ����������۵Ĵ�������������\n",me,who);
    message_vision ("$N�󺰵�����ҩ����ҩ,"+RANK_D->query_rude(me)+"�뺦���ң�\n",me,who);
    who->set("fangcun/panlong_nowayputuo",1);
	destruct (ob);
    return;
  }

	message_vision ("$N��������ɫ��ת�˹���,����Ҳ�������ָ��ˡ�\n",me);
    message_vision ("\n$N��$n˵������л��λ"+RANK_D->query_respect(who)+"�κ����ҵ���ë��,����ʲôҪ���°�æ��һ������.\n",me,who);
    who->delete("fangcun/panlong_nowayputuo");
	who->set_temp("longear_cured",1);
    me->set_temp("cured",1);
	me->command_function("thank "+who->query("id"));
    destruct (ob);
}

object copy_yao ( object me )
{
        object who = new ( "/d/qujing/zhuzi/obj/yao.c");

        who -> set("name", me->query("name"));
        who -> set_temp("is_longear", me->query_temp("is_longear") );
        who -> move(this_object());
        
        return who;
}

