Shader "Unlit/Shader"
{
    Properties
    {
        _MainTex("Texture", 2D) = "white" {}
    }
        SubShader
    {
        // No culling or depth
        Cull Off ZWrite Off ZTest Always

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };

            v2f vert(appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.uv;
                return o;
            }

            //疑似乱数生成関数
            float rand(float3 co)
            {
                return frac(sin(dot(co.xyz ,float3(12.9898,78.233,45.5432))) * 43758.5453);
            }

            sampler2D _MainTex;

            static const float division = 768;
            static const float blackinterval = 6;
            static const int blackheight = 1;
            static const float noisewidth = 0.01;

            fixed4 frag(v2f i) : SV_Target
            {
                //画面Y座標を分割
                int divisionindex = i.uv.y * division;

            //一定間隔で横に区切ったブロックを作る
            int noiseindex = divisionindex / blackinterval;

            //ブロックごとに横にずらす座標を決める前処理
            //時間による乱数のシード値（timeに互いに素っぽい数をかけたのを複数用意するといい感じになる）
            float3 timenoise = float3(0, int(_Time.x * 61), int(_Time.x * 83));
            //ときどき大きくずらす（時間のシード値が変更されるたびに5%の確率でノイズが10倍になる）
            float noiserate = rand(timenoise) < 0.05 ? 10 : 1;

            //横にずらす大きさを乱数で決める（0~1）（時間的にも位置的にもランダムになるように位置によるシード値と時間によるシード値を別次元で与える）
            float xnoise = rand(float3(noiseindex, 0, 0) + timenoise);
            xnoise = xnoise * xnoise - 0.5;             //ずれを2乗して0.5引く（2乗しないと乱れすぎる気がした）
            xnoise = xnoise * noisewidth * noiserate;   //ずれにスケールをかける
            xnoise = xnoise * (_SinTime.w / 2 + 1.1);   //時間的にずれに波があるようにする（いい感じになる気がする）
            xnoise = xnoise + (abs((int(_Time.x * 2000) % int(division / blackinterval)) - noiseindex) < 5 ? 0.005 : 0);    //ラスタースキャンっぽいノイズ

            float2 uv = i.uv + float2(xnoise, 0);

            //ぼやけさせる
            fixed4 col1 = tex2D(_MainTex, uv);
            fixed4 col2 = tex2D(_MainTex, uv + float2(0.005, 0));
            fixed4 col3 = tex2D(_MainTex, uv + float2(-0.005, 0));
            fixed4 col4 = tex2D(_MainTex, uv + float2(0, 0.005));
            fixed4 col5 = tex2D(_MainTex, uv + float2(0,-0.005));
            fixed4 col = (col1 * 4 + col2 + col3 + col4 + col5) / 8;

            col.rgb = divisionindex % blackinterval < blackheight ? float4(0, 0, 0, 1) : col.rgb;
            return col;
        }
        ENDCG
    }
    }
}
