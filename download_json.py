import sys
import json
import subprocess


def load_json_file(filename):
    print(f"Loading JSON file: {filename}")
    with open(filename, 'r', encoding='utf-8') as f:
        return json.load(f)

def download_assets(assets, dir):
    for asset in assets:
        print(f"Downloading asset: {asset['name']}")
        download_url = asset['browser_download_url']
        subprocess.run(['curl', '-s', '-L', '-o', dir + "/" + asset['name'], download_url], check=True)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <json_file>")
        sys.exit(1)
    filename = sys.argv[1]
    data = load_json_file(filename)
    assets = data.get('assets', [])
    dir = filename.rsplit('/', 1)[0]
    download_assets(assets, dir)