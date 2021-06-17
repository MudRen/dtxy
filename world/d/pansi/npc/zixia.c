
//zixiaxianzi.c 2001 by lestat
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_love();
int begin_go();
string ask_mieyao();
string ask_cancel();
void create()
{
       set_name(HIM"��ϼ����"NOR, ({"zixia xianzi", "zixia", "xianzi","master"}));
       set("long", "��������˿���Ŀ�ɽ��ʦ,��˵���Ƿ����һ�õ�о��������޵���
��,����˼���½�ռ�˻���ɽһ������,��ɽ����,������ͽ��\n");
       set("title", HIB"��˿����"NOR);
       set("gender", "Ů��");
       set("age", 20);
       set("class","yaomo");
       set("attitude", "friendly");
       set("rank_info/respect", "С����");
       set("cor", 30);
       set("per", 40);
       set("max_kee", 4500);
       set("max_gin", 800);
       set("max_sen", 4500);
       set("force", 5000);
       set("max_force", 3000);
       set("force_factor", 125);
       set("max_mana", 2500);
       set("mana", 5000);
       set("mana_factor", 250);
       set("combat_exp", 3000000);
	   set("daoxing", 4000000);
       set_skill("literate", 180);
       set_skill("unarmed", 200);
       set_skill("dodge", 200);
       set_skill("force", 180);
       set_skill("parry", 180);
       set_skill("sword", 180);
       set_skill("spells", 170);
       set_skill("whip", 180);
   set_skill("pansi-dafa", 170);
   set_skill("lanhua-shou", 180);
   set_skill("jiuyin-xinjing", 180);
   set_skill("chixin-jian", 180);
   set_skill("qin", 180);
   set_skill("yueying-wubu", 180);
   set_skill("yinsuo-jinling", 200);
   map_skill("spells", "pansi-dafa");
   map_skill("unarmed", "lanhua-shou");
   map_skill("force", "jiuyin-xinjing");
   map_skill("sword", "chixin-jian");
   map_skill("parry", "yinsuo-jinling");
   map_skill("dodge", "yueying-wubu");
   map_skill("whip", "yinsuo-jinling");
   set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: cast_spell, "wuzhishan" :),
                (: cast_spell, "ziqi" :)
        }) );
   set("inquiry", ([
          "����" : (: ask_love :),
  	      "��̨����" : (: begin_go :),
           //"����": (: ask_mieyao :),
           //"cancel": (: ask_cancel :),
]));
create_family("��˿��", 1, "��");
setup();

        carry_object("/d/obj/cloth/tianyi.c")->wear();
        carry_object("/d/pansi/obj/ziqing.c")->wield();
         carry_object("/d/pansi/obj/baohe.c");
        carry_object("/d/ourhome/obj/shoes")->wear();
}

void attempt_apprentice(object ob)
{

   if ( (string)ob->query("family/family_name")=="��˿��") {
   if (((int)ob->query("combat_exp") < 500000 )) {
   command("say " + RANK_D->query_respect(ob) +
"�ĵ��в��������Щ��ѧ�ط�������������\n");
   return;
   }
        command("pat "+ob->query("id"));
        command("say �ã�ϣ��" + RANK_D->query_respect(ob) +
"���Ŭ�������հ���ɱ���Ǹ������ӡ�\n");
       command("recruit " + ob->query("id") );
	   ob->set("title", "����ɽ��˿���ɻ���");
           ob->set("class", "yaomo");
   return;
   }
   command("shake");
   command("say " + RANK_D->query_respect(ob) +
"������ȥѧЩ��������ɡ�\n");
        return;
}
int accept_fight(object me)
{
   return 0;
}

string ask_mieyao()
{
    object who=this_player();
    if((string)who->query("family/family_name")=="��˿��") {
      command("smile "+who->query("id"));
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
int ask_love()
{
        object ob=this_player();
        if(ob->query("family/family_name") != "��˿��")
        {
        command("say ���ֲ�����˿���ģ�ѧ����ʲô?");
        return 1;
        }
        if(ob->query("family/master_name")!= this_object()->query("name"))
        {
        command("say ���ֲ����ҵ�ͽ�ܣ�˭���㣡");
        return 1;
        }
        if(!ob->query("pansi/love_master"))
        {
        ob->set("pansi/love_master",1);
        command("say ��һ�а�����Ϊʦ������������Ӧ�ÿ��԰��㱣���ģ�");
        ob->set("pansi/ask_zixia_go", 1);
        return 1;
	} else
	{
        command("say ��һ�а����Ҳ����Ѿ�����������?");
        return 1;
	}
}

int begin_go()
{
	object me,ob,suo;
    me=this_player();
	ob=this_object();
	if (!me->query("fangcun/panlong_visite"))
	return 0;
	if (me->query("guanli/pansi"))
	  return 0;
	if ((me->query("fangcun/panlong_nowaypansi"))||(me->query("fangcun/panlong_pansi")=="done"))
		return 0;

	if (me->query("fangcun/panlong_pansi")!="begin")
    {
   message_vision("\n\n"NOR,me);
  command("say СŮ�����ҵ�������ʦ��������"+me->query("name")+RANK_D->query_respect(me)+ "ר�����룬��Ӧ����ǰ����
  �أ�����������ϼ������ڶ��ڣ����ֲ�Ը����ƴ���භ������"+me->query("name")+RANK_D->query_respect(me)+ "�����ҵ�
  �������彻����˵���Ǳ���ͬ����������̫����\n\n\n");
  command("sigh ");
   me->set("fangcun/panlong_pansi","begin");
   message_vision(HIM"\n\n\n��ϼ����"+NOR"��$Nһ������ɫ��������\n"NOR,me);
   suo=new("/d/pansi/obj/yinsuo");
   suo->set_temp("zixia_xianzi",1);
   suo->move(me);
	return 1;
	}
	  message_vision(HIM"\n\n\n��ϼ����"+NOR"��$N�����ҽ��������\n"NOR,me);
  return 1;
}

void die()
{
	object qingxia,erlang;
	object me=this_object();
    qingxia=present("qingxia xianzi");
	erlang=present("erlang zhenjun");
   if (!erlang)
	   return ::die();
   if (!qingxia)
	{
	   message_vision(HIY"\n\n\n��꯴Ӷ��ϵ���ֻ�������һ����⣬"+HIM"��ϼ"+HIY"����֮�¶�ܲ��������ԭ�Σ�����һ����о���������ȥ��\n"NOR,me);
	  message_vision(HIY"\n\n\n�����������Ц��������������оҲ�Ҹ���"+HIR"�ѻ�������"+HIY"���֣����ǲ���������\n"NOR,me);
	  message_vision("\n\n\n�Աϼ�һ�����Ц��ȥ��\n"NOR,me);
       destruct(erlang);
      if (present("xiaotian quan"))
        {    
            message("sound", "\n\nХ��ȮҲ�����Ŷ������ﳤ��ȥ��\n\n", environment());
            destruct(present("xiaotian quan"));
        }
      destruct(me);
	  return;
	}
	   message_vision(HIY"\n\n\n��꯴Ӷ��ϵ���ֻ�������һ����⣬"+HIM"��ϼ"+HIY"����֮�¶�ܲ��������ԭ�Σ�����һ����о���������ȥ��\n\n\n"NOR,me);
      destruct(me);
}

