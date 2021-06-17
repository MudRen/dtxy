// modified by vikee 2000.11
//����ɽ���ɡ�dhxy-evil 2000.7.5
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
int ask_me();
int ask_jiu();
int begin_go();
void attempt_apprentice(object ob);

void create()
{
        set_name(HIC"���ʿ"NOR, ({ "zui daoshi", "daoshi", "zui" }));
        set("long", 
"���ʿ�������˵�ʦ�ܣ���Ϊ�þƣ��������������š�\n");

        set("gender", "����");
set("title","��ɽ��");
        set("age", 58);
        set("attitude", "peaceful");
        set("str", 20);
        set("int", 35);
        set("con", 30);
        set("per", 30);
        set("class","swordsman");
        
        set("kee", 2500);
        set("max_kee", 2500);
        set("sen", 3500);
        set("max_sen", 3500);
        set("force", 4000);
        set("max_force", 2000);
        set("max_mana", 3000);
        set("mana", 6000);
        set("force_factor", 80);
        set("mana_factor", 100);

        set("combat_exp", 2500000);
        set("dapxing", 3000000);

        set_skill("spells",180);
        set_skill("force", 180);
        set_skill("dodge", 170);
        set_skill("parry", 150);
        set_skill("sword", 180);
        set_skill("zixia-shengong", 180);
set_skill("sevensteps", 170);
        set_skill("literate", 130);
        set_skill("unarmed", 170);
set_skill("yujianshu",140);
        set_skill("hunyuan-zhang",140);
        set_skill("taoism",180);
        map_skill("spells", "taoism");
        map_skill("dodge", "sevensteps");
        map_skill("force", "zixia-shengong");
map_skill("parry", "yujianshu");
map_skill("sword", "yujianshu");
        map_skill("unarmed", "hunyuan-zhang");

        create_family("��ɽ��", 5, "����");

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: cast_spell, "jianshen" :),
                (: exert_function, "recover" :),
        }) );
   add_temp("apply/damage", 15);
   add_temp("apply/armor", 40);
   set("inquiry", ([
   "ȥ������"     : (: ask_me :),
   "��̨����": (: begin_go :), 
   "����"     : (: ask_jiu :),
]) );
        setup();
        carry_object("d/obj/cloth/daopao")->wear();
        carry_object("/d/obj/weapon/sword/qingfeng")->wield();
}

void attempt_apprentice(object ob)
{
        if ((int)ob->query_int() < 30) 
        {
                command("say ���ҿ�" + RANK_D->query_respect(ob) + "�������ƺ����ʺ�ѧ����ɽ�����书��");
                return;
        }
        if ( ob->query("daoxing") < 150000) {
                command("say " + RANK_D->query_respect(ob) + "�ĵ����ǲ��ǵ͵ĵ㣿");
                return;
        }
        command("say �ðɣ��Ҿ��������ˡ�");
        command("recruit " + ob->query("id"));
}
int ask_me()
{
        object ob=this_player();
if(ob->query("family/family_name") != "��ɽ��")
        {
        command("say ���ֲ�����ɽ���ɵģ�˭���㣡");
        return 1;
        }
        if(ob->query("nyj/shushan")=="done")
        {
          command("say ���ǲ��ǼǴ��ˣ�����������ʹ����˰ɣ�");
          return 1;
        }
        if(ob->query("family/master_name")!= this_object()->query("name"))
        {
        command("say ���ֲ����ҵ�ͽ�ܣ�˭���㣡");
        return 1;
        }
        command("sigh");
        if(ob->query("combat_exp",1)< 500000)
        return notify_fail("��ĵ���̫�ͣ����ǲ�Ҫȥ�����ɣ�");
        command("say �ðɣ�������������ס���ˣ���ȥ�ɣ�");
        if(!ob->query("shushan/jiushen_master"))
        {
        ob->set("shushan/jiushen_master",1);
        command("say ��һ�о�����ΪʦΨһ�ܸ���ģ��������κη������Ӧ�ÿ��԰��㱣���ģ�");
        }
        ob->set("shushan/ask_zuidao_go", 1);
    return 1;
}

int ask_jiu()
{
        object ob=this_player();
if(ob->query("family/family_name") != "��ɽ��")
        {
        command("say ���ֲ�����ɽ���ɵģ�ѧ����ʲô?");
        return 1;
        }
        if(ob->query("family/master_name")!= this_object()->query("name"))
        {
        command("say ���ֲ����ҵ�ͽ�ܣ�˭���㣡");
        return 1;
        }
        if(!ob->query("shushan/jiushen_master"))
        {
        ob->set("shushan/jiushen_master",1);
        command("say ��һ�о�����ΪʦΨһ�ܸ���ģ��������κη������Ӧ�ÿ��԰��㱣���ģ�");
        ob->set("shushan/ask_zuidao_go", 1);
        return 1;
	} else
	{
        command("say ��һ�о����Ҳ����Ѿ�����������?");
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
