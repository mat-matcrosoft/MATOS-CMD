param(
    [Parameter(Mandatory = $true)]
    [string] $ExecutablePath,
    [string] $InstallDirectory = "$env:LOCALAPPDATA\Programs\MatOS-CMD"
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path -LiteralPath $ExecutablePath -PathType Leaf)) {
    throw "Файл программы не найден: $ExecutablePath"
}

New-Item -ItemType Directory -Force -Path $InstallDirectory | Out-Null
$targetPath = Join-Path $InstallDirectory (Split-Path -Leaf $ExecutablePath)
Copy-Item -LiteralPath $ExecutablePath -Destination $targetPath -Force

$currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
$pathEntries = @()
if ($currentPath) {
    $pathEntries = $currentPath -split ';' | Where-Object { $_ }
}

if ($pathEntries -notcontains $InstallDirectory) {
    $newPath = (($pathEntries + $InstallDirectory) -join ';')
    [Environment]::SetEnvironmentVariable("Path", $newPath, "User")
}

Write-Host "MatOS-CMD установлен в $InstallDirectory"
Write-Host "Перезапустите терминал и запустите: Mat-CMD.exe"