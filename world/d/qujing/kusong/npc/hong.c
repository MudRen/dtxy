//Cracked by Roath
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int ask_niang(object me);
int do_yes();
string ask_huohun();
int rank_me();

void create()
{
       set_name("�캢��", ({"honghai er","er"}));
        set("title", "ʥӤ����");
        set("long", "ţħ������ɲŮ�Ķ��ӣ��ڻ���ɽ��������һ��ñ��졣\n");
       set("gender", "����");
       set("age", 16);
        set("per", 25);
        set("str", 55);
        set("int", 25);
        set("con", 25);
        set("spi", 25);

        set("attitude", "heroism");

        set("combat_exp", 2000000);
        set("daoxing", 10000000);

        set("class","yaomo");
        set("max_kee", 6600);
        set("max_sen", 6600);
        set("force", 2500);
        set("max_force", 1600);
        set("force_factor", 100);
        set("max_mana", 1600);
        set("mana", 2500);
        set("mana_factor", 80);
       
        set_skill("unarmed", 200);
        set_skill("dodge", 200);
        set_skill("force", 200);
        set_skill("parry", 200);
        set_skill("spear", 200);
        set_skill("spells", 200);
        set_skill("huoyun-qiang", 200);
        set_skill("moshenbu", 200);
        set_skill("moyun-shou", 200);
        set_skill("huomoforce", 200);
        set_skill("pingtian-dafa", 200);

        map_skill("force", "huomoforce");
        map_skill("spells", "pingtian-dafa");
        map_skill("unarmed", "moyun-shou");
        map_skill("dodge", "moshenbu");
        map_skill("parry", "huoyun-qiang");
        map_skill("spear", "huoyun-qiang");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "spear", "lihuo" :),
        }));
        create_family("���ƶ�", 2, "��");
        setup();
        carry_object("/d/nanhai/obj/huojianqiang")->wield();
        carry_object("/d/qujing/bibotan/obj/zhanpao")->wear();
}

void die()
{
  object ob = query_temp("last_damage_from");
  object me = this_object();
  object che;
  object where = environment();
  message_vision(HIR"\n�캢���ۼ����У�����һ���һ𲻼��ˡ�\n"NOR,ob);
  if( ob->query_temp("fmtd/zhenshen") )
  {
  	che =  present("che",where);
  	destruct(che);
  	che = new("/d/qujing/kusong/obj/cheche");
  	che->set("owner",ob->query("id"));
  	che->move(ob);
  	message_vision(HIR"\n���С��������С��$N����С�Ѿ������ˣ����³�����������\n"NOR,ob);
  }
  destruct(me);
}

void unconcious ()
{
  die();
}