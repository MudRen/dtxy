inherit NPC;
int call_all();
int call_moon();
 int call_wzg();
 int call_kunlun();
 int call_putuo();
  int give_bonnet();
  int call_fangcun();
int call_xueshan();
int call_huoyundong();
    int call_longgong();
int give_gqliwu(object me);
     int call_wdd();
      int call_hell();
        int call_jjf();
		int call_pansi();
int call_shushan();
int call_sanxian();
int give_gift();
#include <ansi.h>
    int give_dan();
    int give_lingzhu();

void remind_dading() {
	command("say 好了！"HIY" 别忘了在客栈拿个大顶(dading)更新你的各项指标\n"NOR);
}

void create()
{
                  set_name("白素贞", ({"bai suzhen","bai", "suzhen"}));
   set ("long", @LONG

传说中的白蛇精，她可以帮你得到你想要的功夫，
你就去问问(ask)她关于各大门派(putuo....)。
LONG);
       set("gender", "女性");
    set("title",HIW"白娘子"NOR);
               set("age", 21);
        set("per", 40);
       set("attitude", "peaceful");
       set("shen_type", 1);
set("inquiry", ([
        "all":(:call_all:),
        "here":(:call_all:),
        "moon":(:call_moon:),
                "huoyundong":(:call_huoyundong:),
              "jjf":(:call_jjf:),
              "wzg":(:call_wzg:),
//"春节快乐":(:give_gqliwu:),
             "xueshan":(:call_xueshan:),
              "fangcun":(:call_fangcun:),
               "putuo":(:call_putuo:),
               "kunlun":(:call_kunlun:),
                "hell":(:call_hell:),
                "longgong":(:call_longgong:),
                 "wdd":(:call_wdd:),
				 "pansi":(:call_pansi:),
           "shushan":(:call_shushan:),
           "sanxian":(:call_sanxian:),
     "魔幻经纶":(:give_bonnet:),
              "gift":(:give_dan:),
              "礼物":(:give_dan:),
              	"lingzhu":(:give_lingzhu:),
]));
        setup();
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
}
}

int call_all() {
	message_vision("$N对着$n说: 我知道的门派有 moon huoyundong jjf wzg xueshan fangcun putuo kunlun hell longgong wdd pansi shushan sanxian\n",this_object(),this_player());
	return 1;
}

int call_moon()
{
  object who=this_player();
           if (this_player()->query("yudian/skills")=="got")
 {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
return 1;
}
who->set_skill("force",100);
who->set_skill("spells",100);
who->set_skill("literate",100);

who->set_skill("dodge",100);
who->set_skill("parry",100);
who->set_skill("unarmed",100);
who->set_skill("moonforce",100);
who->set_skill("moonshentong",100);
who->set_skill("moondance",100);
who->set_skill("baihua-zhang",100);
who->set_skill("jueqingbian",100);
who->set_skill("sword",100);
who->set_skill("snowsword",100);
who->set_skill("whip",100);

who->set_skill("blade",100);
who->map_skill("spells", "moonshentong");
//who->set_skill("xuanhu-blade",100);
who->map_skill("force", "moonforce");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
         remind_dading();
who->set("yudian/skills","got");
return 1;
}
/*    int call_kunlun()
{
 object who=this_player();
if (this_player()->query("yudian/skills")=="got")
{
message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
 return 1;
}
who->set_skill("force",100);
 who->set_skill("mace",100);
who->set_skill("dashen-bian",100);
who->set_skill("wugou-jian",100);
who->set_skill("dodge",100);
who->set_skill("lingyunbu",100);
who->set_skill("force",100);
who->set_skill("xuanzong-force",100);
who->set_skill("yuxu-spells",100);
who->set_skill("unarmed",100);
who->set_skill("sword",100);
who->set_skill("spells",100);
who->set_skill("literate",100);
who->set_skill("kaitian-zhang",100);
who->set_skill("huntian-jian",100);
who->map_skill("spells", "yuxu-spells");
who->map_skill("force", "xuanzong-force");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
command("say 好了！");
who->set("yudian/skills","got");
 return 1;
 }*/
    int call_huoyundong()
{
   object who=this_player();
            if (this_player()->query("yudian/skills")=="got")
  {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
 return 1;
}
  who->set_skill("force",100);
    who->set_skill("spear",100);
      who->set_skill("huoyun-qiang",100);
  who->set_skill("dali-bang",100);
  who->set_skill("dodge",100);
    who->set_skill("stick",100);
  who->set_skill("dali-bang",100);
  who->set_skill("wuyue-spear",100);
  who->set_skill("huomoforce",100);
    who->set_skill("moyun-shou",100);
  who->set_skill("parry",100);
  who->set_skill("pingtian-dafa",100);
  who->set_skill("spells",100);
  who->set_skill("stick",100);
  who->set_skill("unarmed",100);
  who->set_skill("moshenbu",100);
  who->set_skill("literate",100);
  who->map_skill("spells", "pingtian-dafa");
  who->map_skill("force", "huomoforce");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
          remind_dading();
 who->set("yudian/skills","got");
 return 1;
 }
int call_kunlun()
{
  object who=this_player();
           if (this_player()->query("yudian/skills")=="got")
 {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
return 1;
}
who->set_skill("force",100);
who->set_skill("spells",100);
who->set_skill("literate",100);
who->set_skill("dodge",100);
who->set_skill("parry",100);
who->set_skill("unarmed",100);
who->set_skill("xuanzong-force",100);
who->set_skill("yuxu-spells",100);
who->set_skill("lingyunbu",100);
who->set_skill("kaitian-zhang",100);
who->set_skill("mace",100);
who->set_skill("huntian-jian",100);
who->set_skill("dashen-bian",100);
who->set_skill("sword",100);
who->set_skill("wugou-jian",100);
who->map_skill("spells", "yuxu-spells");
who->map_skill("force", "xuanzong-force");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
         remind_dading();
who->set("yudian/skills","got");
return 1;
}
  int call_fangcun()
 {
    object who=this_player();
             if (this_player()->query("yudian/skills")=="got")
   {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
return 1;
  }
 who->set_skill("force",100);
 who->set_skill("spells",100);
 who->set_skill("literate",100);
 who->set_skill("dodge",100);
 who->set_skill("parry",100);
 who->set_skill("unarmed",100);
 who->set_skill("wuxiangforce",100);
 who->set_skill("dao",100);
 who->set_skill("jindouyun",100);
 who->set_skill("puti-zhi",100);
 who->set_skill("sword",100);
// who->set_skill("liangyi-sword",100);
 who->set_skill("qianjun-bang",100);
 who->set_skill("stick",100);
who->map_skill("force", "wuxiangforce");
 who->map_skill("spells", "dao");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
         remind_dading();
 who->set("yudian/skills","got");
return 1;
}
int give_gift()
{
object who=this_player();
         if (this_player()->query("jjf/yudian")=="got")
{
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
  return 1;
}
message_vision("小精灵念动咒语：哈库那玛他他!\n$n突然感觉无比强大。\n",this_object(),this_player());
     who->set("jjf/yudian","got");
return 1;
}
    int call_putuo()
   {
     object who=this_player();
              if (this_player()->query("yudian/skills")=="got")
   {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
return 1;
    }
   who->set_skill("force",100);
   who->set_skill("spells",100);
  who->set_skill("literate",100);
  who->set_skill("dodge",100);
   who->set_skill("parry",100);
  who->set_skill("unarmed",100);
  who->set_skill("jienan-zhi",100);
  who->set_skill("lotusforce",100);
  who->set_skill("buddhism",100);
  who->set_skill("lotusmove",100);
  who->set_skill("staff",100);
  who->set_skill("lunhui-zhang",100);
who->map_skill("spells", "buddhism");
who->map_skill("force", "lotusforce");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
          remind_dading();
  who->set("yudian/skills","got");
return 1;
}
     int call_longgong()
    {
       object who=this_player();
                if (this_player()->query("yudian/skills")=="got")
    {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
 return 1;
    }
   who->set_skill("force",100);
  who->set_skill("spells",100);
   who->set_skill("literate",100);
  who->set_skill("dodge",100);
   who->set_skill("parry",100);
 who->set_skill("unarmed",100);
   who->set_skill("dragonforce",100);
 who->set_skill("seashentong",100);
 who->set_skill("dragonstep",100);
 who->set_skill("dragonfight",100);
 who->set_skill("fork",100);
 who->set_skill("hammer",100);
 who->set_skill("huntian-hammer",100);
 who->set_skill("fengbo-cha",100);
who->map_skill("force", "dragonforce");
who->map_skill("spells", "seashentong");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
          remind_dading();
   who->set("yudian/skills","got");
 return 1;
}
void greeting(object ob)
{
        if( !ob || !visible(ob) || environment(ob) != environment() ) return;
  say(name()+"神秘地说：“想要功夫吗？找我啊！不过，你只有一次机会！”\n");
}
  int call_wdd()
 {
   object who=this_player();
            if (this_player()->query("yudian/skills")=="got")
  {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
return 1;
 }
 who->set_skill("force",100);
 who->set_skill("spells",100);
  who->set_skill("literate",100);
 who->set_skill("dodge",100);
 who->set_skill("parry",100);
 who->set_skill("unarmed",100);
 who->set_skill("huntian-qigong",100);
 who->set_skill("yaofa",100);
 //who->set_skill("dao",100);
 //who->set_skill("throwing",100);
 who->set_skill("lingfu-steps",100);
 who->set_skill("yinfeng-zhua",100);
 who->set_skill("kugu-blade",100);
 who->set_skill("qixiu-jian",100);
 who->set_skill("sword",100);
 who->set_skill("blade",100);
who->map_skill("spells", "yaofa");
who->map_skill("force", "huntian-qigong");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
          remind_dading();
who->set("yudian/skills","got");
 return 1;
}
  int call_xueshan()
 {
   object who=this_player();
            if (this_player()->query("yudian/skills")=="got")
  {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
  return 1;
 }
who->set_skill("force",100);
 who->set_skill("spells",100);
 who->set_skill("dodge",100);
 who->set_skill("parry",100);
 who->set_skill("unarmed",100);
 who->set_skill("literate",100);
 who->set_skill("xiaoyaoyou",100);
 who->set_skill("throwing",100);
 who->set_skill("ningxie-force",100);
 who->set_skill("dengxian-dafa",100);
 who->set_skill("cuixin-zhang",100);
 who->set_skill("bainiao-jian",100);
 who->set_skill("sword",100);
 who->set_skill("bingpo-blade",100);
 who->set_skill("blade",100);
who->map_skill("force", "ningxie-force");
who->map_skill("spells", "dengxian-dafa");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
          remind_dading();
 who->set("yudian/skills","got");
 return 1;
}
  int call_hell()
  {
    object who=this_player();
            if (this_player()->query("yudian/skills")=="got")
  {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
return 1;
}
 who->set_skill("force",100);
  who->set_skill("spells",100);
  who->set_skill("dodge",100);
  who->set_skill("literate",100);
  who->set_skill("parry",100);
  who->set_skill("unarmed",100);
  who->set_skill("ghost-steps",100);
  who->set_skill("gouhunshu",100);
  who->set_skill("tonsillit",100);
  who->set_skill("kusang-bang",100);
  who->set_skill("hellfire-whip",100);
  who->set_skill("jinghun-zhang",100);
  who->set_skill("zhuihun-sword",100);
  who->set_skill("sword",100);
  who->set_skill("stick",100);
  who->set_skill("whip",100);
who->map_skill("force", "tonsillit");
who->map_skill("spells", "gouhunshu");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
          remind_dading();
 who->set("yudian/skills","got");
return 1;
}
   int call_pansi()
    {
       object who=this_player();
                if (this_player()->query("yudian/skills")=="got")
    {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
 return 1;
    }
   who->set_skill("force",100);
  who->set_skill("spells",100);
   who->set_skill("literate",100);
  who->set_skill("dodge",100);
   who->set_skill("parry",100);
 who->set_skill("unarmed",100);
   who->set_skill("jiuyin-xinjing",100);
 who->set_skill("pansi-dafa",100);
 who->set_skill("yueying-wubu",100);
 who->set_skill("lanhua-shou",100);
  who->set_skill("chixin-jian",100);
   who->set_skill("whip",100);
 who->set_skill("sword",100);
 who->set_skill("qin",100);
 who->set_skill("qingxia-jian",100);
 who->set_skill("yinsuo-jinling",100);
who->map_skill("force", "jiuyin-xinjing");
who->map_skill("spells", "pansi-dafa");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
          remind_dading();
   who->set("yudian/skills","got");
 return 1;
}
int call_wzg()
{
  object who=this_player();
           if (this_player()->query("yudian/skills")=="got")
{
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
 return 1;
  }
 who->set_skill("force",100);
who->set_skill("spells",100);
who->set_skill("dodge",100);
who->set_skill("literate",100);
who->set_skill("parry",100);
who->set_skill("unarmed",100);
who->set_skill("baguazhen",100);
who->set_skill("taiyi",100);
who->set_skill("zhenyuan-force",100);
who->set_skill("wuxing-quan",100);
who->set_skill("kaishan-chui",100);
who->set_skill("hammer",100);
who->set_skill("fumo-zhang",100);
who->set_skill("staff",100);
who->set_skill("xiaofeng-sword",100);
who->set_skill("sword",100);
who->set_skill("yange-blade",100);
who->set_skill("blade",100);
who->set_skill("sanqing-jian",100);
who->map_skill("force", "zhenyuan-force");
who->map_skill("spells", "taiyi");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
          remind_dading();
 who->set("yudian/skills","got");
return 1;
}
  int call_jjf()
  {
   object who=this_player();
            if (this_player()->query("yudian/skills")=="got")
   {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
return 1;
 }
 who->set_skill("force",100);
   who->set_skill("spells",100);
   who->set_skill("dodge",100);
   who->set_skill("parry",100);
   who->set_skill("unarmed",100);
   who->set_skill("literate",100);
//   who->set_skill("archery",100);
   who->set_skill("bawang-qiang",100);
   who->set_skill("changquan",100);
   who->set_skill("lengquan-force",100);
   who->set_skill("mace",100);
   who->set_skill("spear",100);
   who->set_skill("axe",100);
   who->set_skill("jinglei-mace",100);
   who->set_skill("sanban-axe",100);
   who->set_skill("wusi-mace",100);
   who->set_skill("yanxing-steps",100);
   who->set_skill("baguazhou",100);
who->map_skill("force", "lengquan-force");
who->map_skill("spells", "baguazhou");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
          remind_dading();
 who->set("yudian/skills","got");
return 1;
}
    int call_shushan()
  {
   object who=this_player();
            if (this_player()->query("yudian/skills")=="got")
   {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
return 1;
 }
 who->set_skill("force",100);
   who->set_skill("spells",100);
   who->set_skill("dodge",100);
   who->set_skill("parry",100);
   who->set_skill("unarmed",100);
   who->set_skill("literate",100);

who->set_skill("hunyuan-zhang",100);
who->set_skill("zixia-shengong",100);
   who->set_skill("yujianshu",100);
   who->set_skill("sword",100);

who->set_skill("sevensteps",100);
who->set_skill("taoism",100);
who->map_skill("force", "zixia-shengong");
who->map_skill("spells", "taoism");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
          remind_dading();
 who->set("yudian/skills","got");
return 1;
}

    int call_sanxian()
  {
   object who=this_player();
            if (this_player()->query("yudian/skills")=="got")
   {
           message_vision("$N对着$n叹了口气。\n",this_object(),this_player());
        command("say 你不是已经要过功夫了吗？何必这样贪心呢！");
return 1;
 }
 who->set_skill("force",100);
   who->set_skill("spells",100);
   who->set_skill("dodge",100);
   who->set_skill("parry",100);
   who->set_skill("unarmed",100);
   who->set_skill("literate",100);
   who->set_skill("binfen-steps",100);
   who->set_skill("mysticism",100);
   who->set_skill("butian-force",100);
   who->set_skill("sword",100);
   who->set_skill("spysword",100);
   who->set_skill("whip",100);
   who->set_skill("wuwei-fuchen",100);
   who->map_skill("dodge", "binfen-steps");
   who->map_skill("parry", "spysword");
   who->map_skill("sword", "spysword");
   who->map_skill("spells", "mysticism");
   who->map_skill("force", "butian-force");
   who->map_skill("whip", "wuwei-fuchen");
message_vision("白素贞念动咒语：@#$%&%*#$##@@!。\n",this_object(),this_player());
          remind_dading();
 who->set("yudian/skills","got");
return 1;
}

int give_dan()
{
object dan;
object who=this_player();
if (!userp(who))
{
command("hate");
command("say 小畜生回去多多修炼！");
command("qi");
return 1;
}
         if (this_player()->query("lestat/gift")=="got")
{
          message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
       command("say 礼物只有一份！领过就不再给了！");
  return 1;
}

who->set("combat_exp",100000);
who->set("daoxing",100000);
who->set("potential",100000);
message_vision("$N手一指，$n只觉得周身紫气环绕，似乎修为有所进境。\n",this_object(),this_player());
     who->set("lestat/gift","got");
return 1;
}


int give_bonnet()

 {

 object bonnet;

 object who=this_player();

if (!userp(who))

{

command("grin");

command("say 什么东西,小心我把你抽筋扒皮？！");

return 1;

}
      bonnet=new("/d/city/npc/obj/faguan");

bonnet->move(who);
message_vision("$N左手一挥，$N变出一个魔幻经纶。\n$N给$n一顶魔幻经纶。\n",this_object(),this_player());

           command("say 好好练哦,如果干了坏事,小心黑山老妖抓你！");

command("snicker");
return 1;
  }

int give_gqliwu(object me)
{
	me=this_player();

 if(me->query("gift/02gq"))   {
    write(HIY"你已经得到了礼物吧？\n"NOR);
			return 1;
	}
          write(HIY"节日快乐!\n你得到了,100年道行，30000武学，30000潜能。\n"NOR);
        me->add("potential",30000);
        me->add("daoxing",100000);
         me->add("combat_exp",30000);
me->set("gift/02gq",1);
        me->save();
	return 1;
}

int give_lingzhu()

 {

 object bonnet;
 int balance;
 object who=this_player();

if (!userp(who))

{

command("grin");

command("say 什么东西,小心我把你抽筋扒皮？！");

return 1;

}
if ( who->query("balance") < 100000 )

{

command("grin");

command("say 宝贝是要拿钱换的，你存款不够十两黄金，想要宝贝？没门！！！");

return 1;

}

      bonnet=new("/d/obj/baowu/tuzhu");
      //balance = who->query("balance")-100000;
//who->set("balance",balance);
bonnet->move(who);
message_vision("$N左手一挥，$N变出一个土灵珠。\n$N给$n一个土灵珠。\n",this_object(),this_player());

command("say 好好练哦,如果干了坏事,小心黑山老妖抓你！");

command("snicker");
return 1;
  }
