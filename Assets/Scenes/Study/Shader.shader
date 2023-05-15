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

            //�^�����������֐�
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
                //���Y���W�𕪊�
                int divisionindex = i.uv.y * division;

            //���Ԋu�ŉ��ɋ�؂����u���b�N�����
            int noiseindex = divisionindex / blackinterval;

            //�u���b�N���Ƃɉ��ɂ��炷���W�����߂�O����
            //���Ԃɂ�闐���̃V�[�h�l�itime�Ɍ݂��ɑf���ۂ������������̂𕡐��p�ӂ���Ƃ��������ɂȂ�j
            float3 timenoise = float3(0, int(_Time.x * 61), int(_Time.x * 83));
            //�Ƃ��ǂ��傫�����炷�i���Ԃ̃V�[�h�l���ύX����邽�т�5%�̊m���Ńm�C�Y��10�{�ɂȂ�j
            float noiserate = rand(timenoise) < 0.05 ? 10 : 1;

            //���ɂ��炷�傫���𗐐��Ō��߂�i0~1�j�i���ԓI�ɂ��ʒu�I�ɂ������_���ɂȂ�悤�Ɉʒu�ɂ��V�[�h�l�Ǝ��Ԃɂ��V�[�h�l��ʎ����ŗ^����j
            float xnoise = rand(float3(noiseindex, 0, 0) + timenoise);
            xnoise = xnoise * xnoise - 0.5;             //�����2�悵��0.5�����i2�悵�Ȃ��Ɨ��ꂷ����C�������j
            xnoise = xnoise * noisewidth * noiserate;   //����ɃX�P�[����������
            xnoise = xnoise * (_SinTime.w / 2 + 1.1);   //���ԓI�ɂ���ɔg������悤�ɂ���i���������ɂȂ�C������j
            xnoise = xnoise + (abs((int(_Time.x * 2000) % int(division / blackinterval)) - noiseindex) < 5 ? 0.005 : 0);    //���X�^�[�X�L�������ۂ��m�C�Y

            float2 uv = i.uv + float2(xnoise, 0);

            //�ڂ₯������
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
