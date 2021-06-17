//����ɽ�ɡ�mhxy-yushu 2001/2
inherit NPC;
#include <ansi.h>
inherit F_MASTER;
   string ask_mieyao();
   string ask_cancel();
string expell_me(object me);
int ask_jiu();
int begin_go();
void create()
{
       set_name("�ƽ���", ({"jiu jianxian", "jianxian", "xian"}));
       set("title", HIC"���ʿ"NOR);   
       set("long", "һ��������š��ƽ��ɡ������ٲ���������������ɽ��֮�ϣ��������ڽ�ͷ����֮�С�\n");
       set("gender", "����");
       set("age", 68);
       set("attitude", "peaceful");
       set("class", "xiake");
       set("str", 30);
       set("int", 30);
       set("per", 10);
       set("con", 30);
       set("combat_exp", 800000);
       set("daoxing", 800000);
       set("max_kee", 1700);
       set("max_sen", 1700);
       set("force", 4000);
       set("max_force", 2000);
       set("force_factor", 120);
       set("max_mana", 2000);
       set("mana", 4000);
       set("mana_factor", 120);
	set_skill("shushan-force", 240);
       set_skill("yujianshu", 260);
       set_skill("sword", 260);
       set_skill("unarmed", 230);
       set_skill("fumozhang", 230); 
       set_skill("dodge", 250);
       set_skill("literate", 110);
       set_skill("force", 250);
       set_skill("parry", 250);
       set_skill("spells", 260);
       set_skill("xianfeng-spells", 260);
       set_skill("zuixian-steps", 250);
       map_skill("dodge", "zuixian-steps");
	map_skill("parry", "yujianshu");
	map_skill("sword", "yujianshu");
       map_skill("force", "shushan-force");
       map_skill("spells", "xianfeng-spells");
       map_skill("unarmed","fumozhang");
       set("chat_chance_combat", 60);
       set("chat_msg_combat", ({
		  (: cast_spell, "fu" :),
                (: perform_action, "sword", "fumo" :),
        }) );
       set("inquiry", ([
                 "��̨����": (: begin_go :), 
	             "��ɽ": (: expell_me :),
                 "leave": (: expell_me :),
                 "kill" : (: ask_mieyao :),
                 "cancel" : (: ask_cancel :),
                 "����" : (: ask_jiu :),

       ]) );
       create_family("��ɽ��", 2, "����");
       setup();
       carry_object("d/obj/cloth/linen")->wear();
       carry_object("d/obj/weapon/sword/qinghong")->wield();
       carry_object("d/qujing/tianzhu/obj/jiuhu");
       carry_object("d/qujing/tianzhu/obj/jiuzhong");
}

void attempt_apprentice(object ob)
{	ob=this_player();
	if( (string)ob->query("family/family_name")=="��ɽ��") {
	if ((int)ob->query("daoxing") < 300000 ) {
  	command("say ��ĵ��л�������" + RANK_D->query_respect(ob) + "������Ŭ�����С�\n");
	return;
	}
       if( (int)ob->query_skill("xianfeng-spells", 1) < 150 ) {
	command("say ��λ" + RANK_D->query_respect(ob) + "����ɷ����������������,�㻹����׷�����������Ű�!\n");
	command("sigh");
	return;
	}
       command("haha");
       command("say �ܺã�" + RANK_D->query_respect(ob) + "���Ŭ�������ձض��гɡ�");
       command("recruit " + ob->query("id") );
	return;
	}
       command("shake");
       command("say ���Ǳ��ɵ���?��" + RANK_D->query_respect(ob) + "������Ѱ���˰ɣ�\n");
       return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) {
                ob->set("class", "xiake");
                ob->set("title", "��ɽ�ƽ��ɵ���");

               } 
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
string ask_mieyao()
{
   object me=this_player();

    if(me->query("family/family_name")!="��ɽ��")
      return ("�㲻�Ǳ�������!");

   command("pat "+me->query("id"));
    command("say ��־����");
   return "/d/obj/mieyao"->query_yao(me);
}
string expell_me(object me)
{       me=this_player();
        if((string)me->query("family/family_name")=="��ɽ��") {
                me->set_temp("betray", 1);
                return ("�����Ҫ�뿪��?��Ҫ����һЩ����,���Ը��(agree)?");
        }
        return ("��֪��");
}
void init()
{
::init();
        add_action("do_agree", "agree");
}

int do_agree(string arg)
{
        if(this_player()->query_temp("betray")) {
                message_vision("$N�����Ը�⡣\n\n", this_player());
                this_player()->add("betray/count", 1);
                this_player()->add("betray/shushan", 1);
		  this_player()->set("combat_exp", this_player()->query("combat_exp")*95/100);
                if( this_player()->query_skill("shushan-force") )
		  this_player()->delete_skill("shushan-force");
                if( this_player()->query_skill("xianfeng-spells") )
		  this_player()->delete_skill("xianfeng-spells");
                this_player()->delete("family");
                this_player()->delete("class");
                this_player()->set("title", "��ͨ����");
                this_player()->save();
                command("say ����ȥ�ɣ�\n");
                return 1;
                }
        return 0;
}

int ask_jiu()
{

    object ob=this_player();
    if(ob->query("family/family_name") != "��ɽ��")
    {
    command("say ���ֲ�����ɽ�ɵģ�˭���㣡");
    return 1;
    }
    if(ob->query("shushan/jiushen_cast"))
    { 
    command("say �㲻���ʹ�����? ");
    return 1;
    }
    if(ob->query("family/master_name") == "�ƽ���" )
    {
    command("say ��һ�о�����ΪʦΨһ�ܸ���ģ��������κη������Ӧ�ÿ��԰��㱣���ģ�");
    ob->set("shushan/jiushen_cast",1);
    return 1;
    }
}


int begin_go()
{
	object me;
    me=this_player();
	if (!me->query("fangcun/panlong_visite"))
	return 0;
	
	if (me->query_temp("fangcun/panlong_shushan_jiujianxian")=="begin")
	{
        message_vision("\n�ƽ���ң����ߵ�����,��,��,�˾�ֻӦ�����У�\n"NOR,me);
		return 1;
    }
    message_vision("\n�ƽ���̾������,��,��,���ƴ�����,Ц̾�����飡\n"NOR,me);
    me->set_temp("fangcun/panlong_shushan_jiujianxian","begin");
	return 1;
}

void return_ob (object ob, object who)
{
  if (ob)
    command ("give "+ob->query("id")+" to "+who->query("id"));
}

void destruct_me (object ob)
{
  destruct (ob);
}

int accept_object (object who, object ob)
{
object jiudai,pass;
string liquid_name;
string liquid_type;
object me = this_object();
liquid_name = YEL"�ɾ�"NOR;
liquid_type = "alcohol";
  if ((string)ob->query("liquid/type")!="alcohol")
   {
     command ("shake "+ob->query("id"));
	call_out ("return_ob",1,ob,who);
    return 1;
  }
  
  if (ob->query("liquid/remaining") == 0)
  {
    message_vision ("$Nҡ��һ��ͷ��˵�����յ�,����ƭ����?\n",me);
    call_out ("return_ob",1,ob,who);
    return 1;
  }
  if (ob->query("liquid/name") != liquid_name)
  {
    message_vision ("$Nҡ��һ��ͷ��˵�������־�Ҳ�Ƶ��Ϻþ�?\n",me);
    call_out ("return_ob",1,ob,who);
    return 1;
  }
  if(!who->query_temp("yaochi_fill"))
  {
	   message_vision ("$Nҡ��ҡͷ��˵�����ⲻ��ƾ���Լ��ı����õ��ľƣ�\n",me);
    call_out ("return_ob",1,ob,who);
    return 1;
    
  }
 
  message_vision (HIW"$Nһ�����ȸ����ɾƿ�����Ц�����þ�,�þƣ�" + RANK_D->query_respect(ob) + ",�����������ȥ,����,���Ǻþư���\n"NOR,me);
  message_vision ("$N����һ���վƺ�«.\n"NOR,me);
  pass=new("/d/shushan/obj/jiujianxian-pass");
  pass->move(who);
  return 1;
  
  
}
�
