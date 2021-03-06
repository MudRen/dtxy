// by lxmas 19/10/2005

#include <ansi.h>
inherit NPC;

void create()
{
  set_name("柔儿", ({"xiao adina", "adina"}));
  set("long", @LONG
她就是传说中的大唐潜能计算机器人，也是海贼王的好老婆，风轻柔。

查询潜能的话，输入以下指令即可:
jisuan AtoBforC 或者jisuan A B C

A 指你的目前skill级别...取值0-3000
B 指你的目标skill级别...取值A-3000
C 指你的悟性...取值10-999
LONG);

       set("gender", "女性");
       set("age", 20);
       set("int", 25+random(5));
       set("title", HIR "潜能计算机器人" NOR);
       set("attitude", "peaceful");
       set("combat_exp", 350000);
       set("daoxing", 10000000);
       set("rank_info/respect", "公主殿下");
       set("class","dragon");
       set("per", 30);
       set("max_kee", 1000);
       set("max_sen", 1000);
       set("force", 3000);
       set("max_force", 3000);
       set("force_factor", 100);
       set("max_mana", 3000);
       set("mana", 3000);
       set("mana_factor", 100);
       set_skill("literate", 500);
       set_skill("unarmed", 500);
       set_skill("dodge", 500);
       set_skill("force", 500);
       set_skill("parry", 500);
       set_skill("fork", 500);
       set_skill("spells", 500);
       set_skill("seashentong", 500);
       set_skill("dragonfight", 500);
       set_skill("dragonforce", 500);
       set_skill("fengbo-cha", 500);
       set_skill("dragonstep", 500);
       map_skill("spells", "seashentong");
       map_skill("unarmed", "dragonfight");
       map_skill("force", "dragonforce");
       map_skill("fork", "fengbo-cha");
       map_skill("parry", "fengbo-cha");
       map_skill("dodge", "dragonstep");
       set("inquiry", ([
                "name": "我就是风轻柔啊，我最会算潜能了。",
                "名字": "我就是风轻柔啊，我最会算潜能了。",
                "姓名": "我就是风轻柔啊，我最会算潜能了。",
                "潜能": "查询潜能的话，输入:jisuan AtoBforC 或者jisuan A B C。",
                "海贼": "海贼是我老公啊，不准欺负我呦，我老公可厉害了。",
                "海贼王": "海贼是我老公啊，不准欺负我呦，我老公可厉害了。",
                "lxmas": "海贼是我老公啊，不准欺负我呦，我老公可厉害了。",
        ]));


       create_family("东海龙宫", 2, "水族");
	setup();

       carry_object("/d/obj/cloth/pinkskirt")->wear();
       carry_object("/d/sea/obj/yincha")->wield();

        remove_call_out ("says");
	call_out("says",3);
}

void says ()
{
  string *msgs = ({
    "$N微笑地看着你，这位小朋友是来算潜能的吗？\n",
    "要算潜能的话，look 我一下就清楚了。$N做了一个鬼脸。\n",
    "怎么？你不算潜能啊？$N有些不高兴了...\n",
    "不算潜能就离开吧，我是喜欢清净的。\n",
    "$N望着天空：我的海贼在哪里呢？\n",
  });
  message_vision (msgs[random(sizeof(msgs))],this_object());
  remove_call_out ("says");
  call_out("says",random(120));
}

void init()
{
add_action("do_jisuan","jisuan");
}

int do_jisuan( string arg )
{
  object me = this_object();
  object who = this_player();
  int sk1,sk2,wx;
  float qn1,qn2,wx2,dh;

  if(this_player()->is_busy())
      return notify_fail("你正忙着呢．．．\n");

  if(!arg) return notify_fail("小朋友，你是不是格式输入错了啊？\n");

  if( sscanf( arg, "%dto%dfor%d", sk1, sk2, wx )==3
	|| sscanf( arg, "%d %d %d", sk1, sk2, wx )==3 );
	else return notify_fail("小朋友，你是不是格式输入错了啊？\n");

  if (wx<10&&wx>=0)
  		write("我说"+who->name()+"，你就"+wx+"点悟性也敢出来混？买个豆腐撞死好了！\n");
  else if (wx>999)
    	write("挖靠，大家快看，"+who->name()+"的悟性没有封顶？你个大bug！被我发现你死定了！\n");
  else if (sk1<0||sk1>3000)
     write("巫师注意了，"+who->name()+"的武功有问题，绝对用了bug，现已通知lxmas，等待秋后问斩吧！\n");
  else if (sk2<0||sk2>3000)
     write("巫师注意了，"+who->name()+"的武功有问题，绝对用了bug，现已通知lxmas，等待秋后问斩吧！\n");
  else if (sk1>sk2)
     write("哇塞，"+who->name()+"已经练的返老还童了！\n");
  else if (sk1==sk2)
	 write("耍我啊，这个你不会自己算？亏你还有"+wx+"点悟性，白搭了！\n");
  else if (sk1>=0&&sk1<=3000&&sk2>sk1&&sk2<=3000&&wx>9&&wx<=999) {
       if (sk1==0)
          qn1=1.0*sk2*(sk2+1)*(2*sk2+1)/(3*wx);
        else
          qn1=1.0*sk2*(sk2+1)*(2*sk2+1)/(3*wx)-sk1*(sk1+1)*(2*sk1+1)/(3*wx);
        qn2=1.0*4*qn1;
        wx2=1.0*(sk2-1)*(sk2-1)*(sk2-1)/10;
        dh=1.0*wx2/1000;
        write("阁下可是"+who->name()+"? \n您从"+sk1+"修炼到"+sk2+"级，需要潜能"+qn1+"点，四倍切磋需要潜能"+qn2+"点。\n");
        write("同时您还需要有"+wx2+"点武学支持，法术学习需要"+dh+"年道行支持。\n");
  }
  else write("小朋友，你是不是格式输入错了啊？\n");
  return 1;
}