#include "Sound.h"

#include <windows.h>
#include <cassert>
#include <fstream>
#pragma comment(lib,"xaudio2.lib")

Sound* Sound::GetInstance()
{
	static Sound instance;

	return &instance;
}

void Sound::Initialize(const std::string& directoryPath)
{
	directoryPath_ = directoryPath;

	HRESULT result;

	IXAudio2MasteringVoice* masterVoice;

	// XAudioエンジンのインスタンスを生成
	result = XAudio2Create(&xAudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(result));

	// マスターボイスを生成
	result = xAudio2_->CreateMasteringVoice(&masterVoice);
	assert(SUCCEEDED(result));
}

void Sound::Finalize()
{
	// XAudio2解放
	xAudio2_.Reset();
	// 音声データ解放

	std::map<std::string, SoundData>::iterator it = soundDates_.begin();

	for (; it != soundDates_.end(); ++it) {
		Unload(&it->second);
	}
	soundDates_.clear();
}

void Sound::LoadWave(const std::string& filename)
{
	if (soundDates_.find(filename) != soundDates_.end()) {
		//重複読み込みなので、何もせず抜ける
		return;
	}

	//ディレクトリパスとファイル名を連結してプルパスを得る
	std::string fullpath = directoryPath_ + filename;

	// ファイル入力ストリームのインスタンス
	std::ifstream file;
	// .wavファイルをバイナリモードで開く
	file.open(fullpath, std::ios_base::binary);
	// ファイルオープン失敗を検出する
	assert(file.is_open());

	// RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}
	// タイプがWAVEかチェック
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}

	// Formatチャンクの読み込み
	FormatChunk format = {};
	// チャンクヘッダーの確認
	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}
	// チャンク本体の読み込み
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	// Dataチャンクの読み込み
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	// JUNKチャンクを検出した場合
	if (strncmp(data.id, "JUNK ", 4) == 0) {
		// 読み取り位置をJUNKチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		// 再読み込み
		file.read((char*)&data, sizeof(data));
	}

	if (strncmp(data.id, "data ", 4) != 0) {
		assert(0);
	}

	// Dataチャンクのデータ部（波形データ）の読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);

	// Waveファイルを閉じる
	file.close();

	// returnする為の音声データ
	SoundData soundData = {};

	soundData.wfex = format.fmt;
	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData.bufferSize = data.size;

	//サウンドデータを連想配列に格納
	soundDates_.insert(std::make_pair(filename, soundData));
}

void Sound::Unload(SoundData* soundData)
{
	// バッファのメモリを解放
	delete[] soundData->pBuffer;

	soundData->pBuffer = 0;
	soundData->bufferSize = 0;
	soundData->wfex = {};
}

void Sound::PlayWave(const std::string& filename)
{

	HRESULT result;

	std::map<std::string, SoundData>::iterator it = soundDates_.find(filename);
	//未読み込みの検出
	assert(it != soundDates_.end());
	//サウンドデータの参照を取得
	SoundData& soundData = it->second;

	// 波形フォーマットを元にSourceVoiceの生成
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2_->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
	assert(SUCCEEDED(result));

	// 再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = soundData.pBuffer;
	buf.AudioBytes = soundData.bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	// 波形データの再生
	result = pSourceVoice->SubmitSourceBuffer(&buf);
	result = pSourceVoice->Start();
}
