//Cracked by Roath

inherit NPC;
#include <ansi.h>
void create()
{
	set_name("¹ÛÒôÆĞÈø", ({ "guanyin pusa", "guanyin", "pusa" }));
	set("title", "¾È¿à¾ÈÄÑ´ó´È´ó±¯");
	set("long", @LONG
ÀíÔ²ËÄµÂ£¬ÖÇÂú½ğÉí¡£Ã¼ÈçĞ¡ÔÂ£¬ÑÛËÆË«ĞÇ¡£À¼ĞÄĞÀ×ÏÖñ£¬
Ş¥ĞÔ°®µÃÌÙ¡£Ëı¾ÍÊÇÂäÙ¤É½ÉÏ´È±¯Ö÷£¬³±Òô¶´Àï»î¹ÛÒô¡£
LONG);
	set("gender", "Å®ĞÔ");
	set("age", 35);
	set("attitude", "peaceful");
	set("rank_info/self", "Æ¶É®");
	set("rank_info/respect", "ÆĞÈøÄïÄï");
	set("class", "bonze");
	set("family/family_name","ÄÏº£ÆÕÍÓÉ½");
  set("str",60);
	set("per",100);//means no rong-mao description.
	set("max_kee", 5000);
	set("max_gin", 5000);
	set("max_sen", 5000);
	set("force", 4000);
	set("max_force", 2000);
	set("force_factor", 240);
	set("max_mana", 3000);
	set("mana", 6000);
	set("mana_factor", 240);
	set("combat_exp", 2000000);
	set("daoxing", 10000000);

	set_skill("literate", 260);
	set_skill("spells", 260);
	set_skill("buddhism", 260);
	set_skill("unarmed", 260);
	set_skill("jienan-zhi", 260);
	set_skill("dodge", 260);
	set_skill("lotusmove", 260);
	set_skill("parry", 260);
	set_skill("force", 260);
	set_skill("lotusforce", 260);
	set_skill("staff", 260);
	set_skill("lunhui-zhang", 260);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "unarmed", "lingxi" :),
		(: perform_action, "unarmed", "rulai" :),
	}) );

	setup();
	carry_object("/d/nanhai/obj/jiasha")->wear();
	//carry_object("/d/nanhai/obj/nine-ring")->wield();
}

void announce_success (object who)
{
  
  int i;

  if(!who) return;

  if (who->query("combat_exp") < 10000)
    return;
  if (who->query("obstacle/huoyun") == "done")
    return;
  if (! who->query_temp("obstacle/hong_killed"))
    return;
  if (who->query("obstacle/wuji") != "done")
    return;  

  	i = random(700);
  who->add("obstacle/number",1);
  who->set("obstacle/huoyun","done");
  who->add("daoxing",i+3000);
  command("chat "+who->query("name")+"¿İËÉ½§»ğÔÆ¶´.ÊÕ·şºìº¢¶ù");
  message("channel:chat",HIY"¡¾¹ı¹ØÕ¶½«¡¿¹ÛÒôÆĞÈø(guanyin pusa)£º"+who->query("name")+"´³¹ıÎ÷ĞĞÈ¡¾­[1;37mµÚÊ®ËÄ¹Ø£¡\n"NOR,users());
  tell_object (who,"ÄãÓ®µÃÁË"+chinese_number(3)+"Äê"+
              chinese_number(i/4)+"Ìì"+
               chinese_number((i-(i/4)*4)*3)+"Ê±³½µÄµÀĞĞ£¡\n");
  who->save();
}
void die()
{
        if( environment() ) 
        	message("sound", "\n¹ÛÒôÆĞÈøÒ»¿´ÊÆÍ·²»¶Ô£¬¼İÏéÔÆ£¬µÇ²ÊÎí£¬¾¶ÍùÎ÷·½È¥ÁË¡£¡£¡£\n\n", environment());
	destruct(this_object());
}
void unconcious()
{
	die();
}