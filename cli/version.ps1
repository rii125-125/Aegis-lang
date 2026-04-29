$owner = "rii125-125"
$repo = "Aegis-lang"
$url = "https://api.github.com/repos/$owner/$repo/releases/latest"

$outPutFile = "../test/lasted_version.txt"

try {
    $release = Invoke-RestMethod -Uri $url
    $lastVer = $release.tag_name

    $lastVer | Out-File -FilePath $outPutFile -Encoding utf8

    Write-Host "Success!: Last version($lastVer) -> $outPutFile in save." -ForegroundColor Green
}
catch {
    Write-Error "Error: Not found Error.($_.Exception.Message)"
}