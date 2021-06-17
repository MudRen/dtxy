// guanyin.c ��������
// By ����(take) 


inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int begin_go();
int do_drop(object, object);

string ask_mieyao();
string ask_cancel();

void create()
{
	set_name("��������", ({ "guanyin pusa", "guanyin", "pusa" }));
	set("title", "�ȿ���Ѵ�ȴ�");
	set("long", @LONG
��Բ�ĵ£���������ü��С�£�����˫�ǡ�����������
ޥ�԰����١���������٤ɽ�ϴȱ�������������������
LONG);
	set("gender", "Ů��");
	set("age", 35);
	set("attitude", "peaceful");
	set("rank_info/self", "ƶɮ");
	set("rank_info/respect", "��������");
	set("class", "bonze");
        	set("str",24);
	set("per",100);//means no rong-mao description.
	set("max_kee", 5000);
	set("max_gin", 5000);
	set("max_sen", 5000);
	set("force", 4000);
	set("max_force", 2000);
	set("force_factor", 145);
	set("max_mana", 3000);
	set("mana", 6000);
	set("mana_factor", 150);
	set("combat_exp", 2000000);
	set("daoxing", 10000000);

	set_skill("literate", 150);
	set_skill("spells", 200);
	set_skill("buddhism", 200);
	set_skill("unarmed", 150);
	set_skill("jienan-zhi", 150);
	set_skill("dodge", 180);
	set_skill("lotusmove", 180);
	set_skill("parry", 180);
	set_skill("force", 180);
	set_skill("lotusforce", 180);
	set_skill("staff", 180);
	set_skill("lunhui-zhang", 180);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		//(: cast_spell, "bighammer" :),
		(: perform_action, "staff", "chaodu" :),
		(: perform_action, "staff", "pudu" :),
	}) );
	set("inquiry",([
      "��̨����"    : (: begin_go :),
      "cancel": (: ask_cancel :),
      "����": (: ask_mieyao :),
      "��ƿ": "ǰЩ�죬���ǽ��ҵľ�ƿ�ã�������Ҳû�л�����ȥ�����ɡ�" ]));

	//let's use cast bighammer to protect her...weiqi:)
	create_family("�Ϻ�����ɽ", 1, "����");

	setup();
	carry_object("/d/nanhai/obj/jiasha")->wear();
	carry_object("/d/nanhai/obj/nine-ring")->wield();
}

string ask_mieyao()
{
    object who=this_player();
        
    if((string)who->query("family/family_name")=="�Ϻ�����ɽ") {
      command("say ������ħ�����ҷ�������֮���֡�");
      return "/d/obj/mieyao"->query_yao(who);
    }
    return ("��������,�ι�����?\n");
}

string ask_cancel()
{
	object me=this_player();
	if((int)me->query_temp("m_mieyao"))
	{
	      me->add("daoxing",-2000);
	      me->delete_temp("m_mieyao");
	      me->delete("secmieyao");
	      me->delete("secmieyao/type");
	      me->delete("secmieyao/location");
	      me->delete("secmieyao/place");
	      me->delete("secmieyao/name");
	      me->delete("secmieyao/id");
	     return ("û�õĶ�����");
	}
	else
	{
	     return ("���������𣿣�");
	}
}

void attempt_apprentice(object ob)
{
	if (!((string)ob->query("bonze/class") =="bonze" )) {
		command("say �ҷ�����ͨ���" + RANK_D->query_respect(ob) + "�����������������š�\n");
		write("�����ӹ�����������δ��ȳ�����Ϊ���졣\n");
		return;
	}	
	if (((int)ob->query_skill("buddhism", 1) < 100 )) {
		command("say " + RANK_D->query_respect(ob) + "���ڷ��Ͽ��ޣ������ѳ�������\n");
		return;
	}
	command("pat " + ob->query("id") );
	command("say �ã�������ҷ��ŵĺõ��ӡ�ֻҪ���Ŭ�����������������\n");

	command("recruit " + ob->query("id") );
	return;	
}
void die()
{
	int i;
	string file;
	object *inv;
	object who = query_temp("last_damage_from");
	object hong;
	if( objectp(who) && who->query_temp("huohun/zhenshen") )
	{
		who->delete_temp("huohun/zhenshen");
		hong = present("honghai er",environment());
		if( hong && random(who->query("int")) > 20 - random( who->query("lunhui_zhuanshi") ) )
		{
			who->add("huohun_known",1);
   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���캢��(honghai er)��" + who->name() + "���Ҷ����������������"+HIR"[���]"+HIC"��\n\n\n"NOR,users());
		}
		else
		{
			who->set("huohun_cant",1);
   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���캢��(honghai er)��" + who->name() + "��Ȼ�ɹ����Ҷ������ȴ��Եѧϰ"+HIR"[���]"+HIC"���ǿ�ϧ��\n\n\n"NOR,users());
		}
		if( hong )
		{
			message_vision(HIR"\n\n�캢���ۼ�ʱ���ѵ�������һ�ź�������ɽ����ƶ���ȥ��\n"NOR,who);
			destruct(hong);
		}
		
	}
        if( environment() ) {
        message("sound", "\n\n��������ҡͷ̾�����������ϣ�����ħ�ϣ����伲�࣬���˶�֮��\n\n", environment());
        command("sigh");
        message("sound", "\n�������������ƣ��ǲ�����������ȥ�ˡ�����\n\n", environment());
        inv = all_inventory(this_object());
	for(i=0; i<sizeof(inv); i++) {
		if (inv[i]->query("no_drop")) continue;
		do_drop(this_object(), inv[i]);
//		if (stringp(file = find_command("drop")) && 
//			call_other(file, "do_drop", this_object(), inv[i])) ;
	}
	}

	destruct(this_object());
}

int do_drop(object me, object obj) {
  if (obj->move(environment(me))) {
      //d_mana>0 is for "bian". mon 11/05/97
      if((obj->query_temp("d_mana"))>0) {
            if( obj->query_temp("is_living")==1 )
                 message_vision("$N��$n�ӱ��Ϸ������������ڵ��ϡ�\n", me, obj);
            else {
                 message_vision( sprintf("$N����һ%s$n��\n",
                 undefinedp(obj->query_temp("unit"))?
	                 "��":obj->query_temp("unit")
                         ), me, obj );
           }
      } else {
           if( obj->is_character() )
                  message_vision("$N��$n�ӱ��Ϸ������������ڵ��ϡ�\n", me, obj);
           else {
             message_vision( sprintf("$N����һ%s$n��\n", obj->query("unit")),
                     me, obj );
             if( !obj->query("value") && !obj->value() ) {
                tell_object(me,"��Ϊ������������ֵǮ���������ǲ�����ע�⵽���Ĵ���
		   ��\n");
                destruct(obj);
             }
           }
      }
      return 1;
  }
  return 0;
}


void unconcious()
{
	die();
}

int accept_object(object me,object ob)
{       
	    string myname=RANK_D->query_respect(me), thing=(string)ob->query("id");
		object who;
        who=this_object();
      
	if (me->query("fangcun/panlong_putuo")=="begin")
	{
	  if (ob->query("name") == "���������š�")
      {
      command ("nod");
      command ("say ���ǳ�������������ֵĵ������ţ�");
      me->set_temp("putuo/basic_blade","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "��ȭ�����š�")
      {
      command ("nod");
      command ("say ���ǳ�������������ֵ�ȭ�����ţ�");
      me->set_temp("putuo/basic_unarmed","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "�����¾���")
      {
      command ("smile");
      command ("say ���ǳ��ٹ�������ڲؾ�¥�ĵ��¾�������̨����ɽ�ľ����е��ղ��أ�");
     me->set_temp("putuo/daode","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "����ħɽ�ľ���")
      {
      command ("ah");
      command ("say �Ȿ����ħɽ�ľ����̺��������߲��ٵ���Ѫ,�����Ȿ����ʵ���ף�");
     me->set_temp("putuo/forcebook","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "��Ů������")
      {
      command ("nod");
      command ("say �Ȿ��Ů���������¹���������Ϊ��Ů���Ӷ���ʶ��֮�ã�");
     me->set_temp("putuo/girlbook","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
      if (ob->query("name") == "���������ס�")
      {
      command ("nod");
      command ("say ����ʫ��֮��,ֻ�����ù𻨾ƻ����ģ�");
     me->set_temp("putuo/jianpu","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "����վ���")
      {
      command ("bow");
      command ("say �����ҷ�����֮��ɷ�,һֱ�����Ϻ�������Ժ�У�");
     me->set_temp("putuo/jingang","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "�����顽")
      {
      command ("nod");
      command ("say ���ǳ����Ƕ�,���Ͻ��ڵ���ѧ�鼮,��������˵��������棬����ﵣ��٣�ǹ���ȣ�������ʮ�ֻ����书��");
     me->set_temp("putuo/misc","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "���������顽")
      {
      command ("nod");
      command ("say ����Ԭ�سϴ������ķ���Ҫ�죡");
     me->set_temp("putuo/nowords","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "�����ؾ���")
      {
      command ("nod");
      command ("say "+RANK_D->query_respect(me)+ "������Ա���ȥǿ��,Ʒ�пɼΣ�");
     me->set_temp("putuo/parry_book","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "��ǧ���ġ�")
      {
      command ("nod");
      command ("say ����̨����ɽ�����ӵ�������ġ�ǧ���ġ���");
     me->set_temp("putuo/qian","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "��ȭ����")
      {
      command ("nod");
      command ("say ���ǳ�����ݷ���ƽ���ظ񶷼��ɣ�");
     me->set_temp("putuo/quanjing","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
      if (ob->query("name") == "�����־���")
      {
      command ("nod");
      command ("say �⡼���־���һ�����Ϻ�������Ժ,���������Լ��¹������������д���,�������������㣮");
     me->set_temp("putuo/san","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	   if (ob->query("name") == "��ǹ����顽")
      {
      command ("nod");
      command ("say ���Ǵ��ƽ������ڵĲ���,������ǹ�������ã�");
     me->set_temp("putuo/spearbook","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	   if (ob->query("name") == "���ȷ���Ҫ��")
      {
      command ("nod");
      command ("say �������Ϻ�������Ժ֮�");
     me->set_temp("putuo/staffbook","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "�鲼ͷ")
      {
      command ("hmm");
      command ("say ���鲼ͷմ��ɱ��,"+RANK_D->query_respect(me)+ "Ϊ����һ����֮���ɱ�䣿");
     me->set_temp("putuo/stickbook","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "����ˮ��")
      {
      command ("nod");
      command ("say ���Ƕ����������ϸ��˵ļҴ��鼮��");
     me->set_temp("putuo/windwater","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  else
      {
      command ("say ����ʲô��");
      call_out("dropthing", 1, thing);
      return 1;
      }
     }
  else
  command ("shake ");
  return 0;
}
void destroy(object ob)
{
        destruct(ob);
        return;
}

void dropthing(string thing)
{
  command("drop "+thing);
  return;
}

int begin_go()
{
	object me,ob;
    int dx,dx1,wx,qn;
	me=this_player();
	ob=this_object();
	dx=(me->query("daoxing"))/20;
if (dx>=100000) dx=100000;
	dx1=dx/1000;
	wx=(me->query("combat_exp"))/20;
if (wx>=10000) wx=10000;
	qn=30000;
    
		if (!me->query("fangcun/panlong_visite"))
	return 0;
		if (me->query("guanli/putuo"))
	return 0;

		if (me->query("fangcun/panlong_putuo")=="done")
	{
        message_vision(HIW"\n����������Ȼ"+RANK_D->query_respect(me)+ "����,������Ͷ���ɣ�\n"NOR,me);
        message_vision(HIY"\n����������Ȼ�������������������Ƕ���ȥ��\n"NOR,me);
		ob->move("/d/lingtai/inside1");
        return 1;
	}
   		
		if ((me->query_temp("putuo/basic_blade")=="done") 
			&& (me->query_temp("putuo/basic_unarmed")=="done")
			&& (me->query_temp("putuo/daode")=="done")
			&& (me->query_temp("putuo/forcebook")=="done")
			&& (me->query_temp("putuo/girlbook")=="done")
			&& (me->query_temp("putuo/jianpu")=="done")
			&& (me->query_temp("putuo/jingang")=="done")
			&& (me->query_temp("putuo/misc")=="done")
			&& (me->query_temp("putuo/nowords")=="done")
			&& (me->query_temp("putuo/parry_book")=="done")
			&& (me->query_temp("putuo/qian")=="done")
			&& (me->query_temp("putuo/quanjing")=="done")
			&& (me->query_temp("putuo/san")=="done")
			&& (me->query_temp("putuo/spearbook")=="done")
			&& (me->query_temp("putuo/staffbook")=="done")
			&& (me->query_temp("putuo/stickbook")=="done")
			&& (me->query_temp("putuo/windwater")=="done"))
	{
		me->add("fangcun/panlong_visite",1);
		me->set("fangcun/panlong_putuo","done");
       message("chat",HIC+"��"+HIW+"��������"+HIC+"����������(Guanyin pusa)��"+me->query("name")+"����������ѧ��Ҫ,��ʱƶɮһ������̨����\n"NOR,users());
             message("chat",HIC+"��"+HIW+"��������"+HIC+"����������(Guanyin pusa)��"+me->query("name")+"�õ�����������"+chinese_number(dx1)+"�꣬��ѧ"+wx+"�㣬Ǳ��30000�㣮\n"NOR,users());
		if (me->query("family/family_name")=="����ɽ���Ƕ�")
           message_vision("\n����������������֮�ջ���" + RANK_D->query_respect(me) + "������֪һ��.\n"NOR,me);
		me->add("daoxing",dx);
		me->add("combat_exp",wx);
		me->add("potential",30000);
	    if ((me->query("family/family_name")!="����ɽ���Ƕ�")||(me->query("fangcun/panlong_noway")))
			me->set("guanli/putuo",1);
		return 1;
	}				
		if ((me->query("fangcun/panlong_putuo")!="begin")&&(me->query("fangcun/panlong_visite")))
    {
  command("say "+me->query("name")+"���Ĳ�����,����Ϊ�ռ������������л�����ѧ�鼮æµ,Ҫȥ��̨����ֻ��û�п��У�\n");
  command("sigh ");
   me->set("fangcun/panlong_putuo","begin");
	return 1;
	}

  message_vision("\n�����������������˵������˵˳�����Ϣ��ͨ,����������ѧ�鼮������,��Ӧ��������֪.\n"NOR,me);
  return 1;
}

�
